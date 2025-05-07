#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::identifier() {
    if (isType(Token::Word))
      return new Identifier(std::move(get(-1).value));

    return value();
  }
} // namespace wind::wdlang