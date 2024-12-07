#include "wind/language/language.hpp"

#undef main

static std::string
join(const std::list<std::string>& lst, const std::string& delimiter) {
  std::ostringstream oss;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    oss << *it;
    if (std::next(it) != lst.end()) {
      oss << delimiter;
    }
  }
  return oss.str();
}

namespace wind {
  namespace wi {
    class Wi2Cpp : public LangImpl {
    protected:
      void compile(Value* expression) override {
        spdlog::info("value: {}", expression->value);
      }

      void compile(Identifier* expression) override {
        spdlog::info("identifier: {}", expression->name);
      }

      void compile(UnaryOperation* expression) override {
        spdlog::info("unary-operation: {}", (int)expression->type);
        expression->operand->execute(this);
      }

      void compile(BinaryOperation* expression) override {
        spdlog::info("binary-operation: {}", (int)expression->type);
        expression->lhs->execute(this);
        expression->rhs->execute(this);
      }

      void compile(AssignStatement* statement) override {
        spdlog::info("assign-statement: {}", statement->name);
        statement->value->execute(this);
      }

      void compile(VariableStatement* statement) override {
        spdlog::info(
          "variable-statement: (name: {}, type: {}, mutable: {})",
          statement->name,
          statement->type,
          statement->isMutable
        );
        statement->value->execute(this);
      }

      void compile(ClassMember* member) override {
        spdlog::info("class-member: {}", (int)member->access);
        member->member->execute(this);
      }

      void compile(ClassStatement* statement) override {
        auto interfaces = join(statement->interfaces, ",");
        spdlog::info(
          "class-statement: (name: {}, extends: {}, interfaces: [{}])",
          statement->name,
          statement->parent,
          interfaces
        );

        for (auto member : statement->members)
          member->execute(this);
      }

      void compile(FunctionArgumentStatement* arg) override {
        spdlog::info(
          "function-argument: (name: {}, type: {}, hasDefaultValue: {})",
          arg->name,
          arg->type,
          (arg->defaultValue != nullptr)
        );
        if (arg->defaultValue)
          arg->defaultValue->execute(this);
      }

      void compile(FunctionStatement* statement) override {
        spdlog::info(
          "function-statement: (name: {}, return-type: {})",
          statement->name,
          statement->type
        );

        for (auto arg : statement->args)
          arg->execute(this);

        for (auto part : statement->body)
          part->execute(this);
      }

      void compile(ReturnStatement* statement) override {
        spdlog::info("return-statement");
        if (statement->value)
          statement->value->execute(this);
      }
    };
  } // namespace wi
} // namespace wind

int dep_main() {
  wind::wi::Tokenizer t(
    R"(
      class Player extends Container implements A, B {
      public:
        let mut x: i32 = 3

        i32 add(a: i32, b: i32, c: i32 = 5) -> a + b + c

        void update() {
          let y: i8 = 255
          let z: f32 = 100

          x = x * (y - z) / -(100 + x)
        }
      private:
        let canMove: bool = false

        string getName() {
          return "NeutrinoZh"
        }
      }
    )"
  );

  wind::wi::AST ast(t.getStream());

  auto errors = ast.getErrors();
  bool failed = !errors.empty();
  while (!errors.empty()) {
    auto error = errors.front();
    errors.pop();
    spdlog::info(
      "({}, {}): {}: '{}'",
      error.line,
      error.position,
      error.message,
      error.token.value
    );
  }

  if (failed)
    return 0;

  std::string ss = "";
  auto root = ast.getRoot();
  auto wdl2cpp = new wind::wi::Wi2Cpp();
  for (auto el : root) {
    el->execute(wdl2cpp);
  }

  std::cout << ss << "\n";
}
