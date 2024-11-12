#include "wind/language/language.hpp"

#undef main

int main() {
  wind::wdlang::Tokenizer t(
    R"(
      23 + {
    )"
  );

  wind::wdlang::AST ast(t.getStream());
  auto errors = ast.getErrors();
  while (!errors.empty()) {
    auto error = errors.front();
    spdlog::info("({}, {}): {}: '{}'", error.line, error.position, error.message, error.token.value);
  }
}