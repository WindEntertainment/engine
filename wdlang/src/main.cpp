#include "wind/language/language.hpp"

#undef main

namespace wind {
  namespace wdlang {
    class Wdl2Cpp : public LangImpl {
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
        spdlog::info("variable-statement: (name: {}, type: {}, mutable: {})", statement->name, statement->type, statement->isMutable);
        statement->value->execute(this);
      }
    };
  }
}

int main() {
  wind::wdlang::Tokenizer t(
    R"(
      let x: i32 = 0
      x = (x - 1) * 2
      let mut y: i8 = x * (x - x / 2)
    )"
  );

  wind::wdlang::AST ast(t.getStream());
  
  auto errors = ast.getErrors();
  bool failed = !errors.empty();
  while (!errors.empty()) {
    auto error = errors.front();
    errors.pop();
    spdlog::info("({}, {}): {}: '{}'", error.line, error.position, error.message, error.token.value);
  }

  if (failed)
    return 0;

  std::string ss = "";
  auto root = ast.getRoot();
  auto wdl2cpp = new wind::wdlang::Wdl2Cpp();
  for (auto el : root) {
    el->execute(wdl2cpp);
  }

  std::cout << ss << "\n";
}