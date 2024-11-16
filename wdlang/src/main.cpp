#include "wind/language/language.hpp"

#undef main

namespace wind {
  namespace wdlang {
    class Wdl2Cpp : public LangImpl {
    protected:
      void compile(Value* expression) override { 
        spdlog::info("value");
      }

      void compile(Identifier* expression) override {
        spdlog::info("identifier");
      }

      void compile(UnaryOperation* expression) override {
        spdlog::info("unary-operation");
        expression->operand->execute(this);
      }

      void compile(BinaryOperation* expression) override {
        spdlog::info("binary-operation");
        expression->lhs->execute(this);
        expression->rhs->execute(this);
      }
    };
  }
}

int main() {
  wind::wdlang::Tokenizer t(
    R"(
      23 + 12
    )"
  );

  wind::wdlang::AST ast(t.getStream());
  
  auto errors = ast.getErrors();
  while (!errors.empty()) {
    auto error = errors.front();
    spdlog::info("({}, {}): {}: '{}'", error.line, error.position, error.message, error.token.value);
  }

  std::string ss = "";
  auto root = ast.getRoot();
  auto wdl2cpp = new wind::wdlang::Wdl2Cpp();
  for (auto el : root) {
    el->execute(wdl2cpp);
  }

  std::cout << ss << "\n";
}