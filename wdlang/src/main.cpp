#include "wind/language/language.hpp"

#undef main

int main() {
  wind::wdlang::Tokenizer t(
    R"(
      class Program {
      public:
        void main() {
          spdlog::info("Hello, World!");
        }  
      }
    )"
  );

  auto& stream = t.getStream();
  auto token = stream.get();
  for (; token != stream.end(); token = stream.get()) {
    spdlog::info("Token({}:{}) type: {}, value: '{}'", stream.line, stream.position, (int)token.type, token.value);
  }
}