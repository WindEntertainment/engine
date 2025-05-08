#include "wind/language/language.hpp"
#include "wind/language/nodes/Identifier.hpp"

namespace wind::wdlang {
  Node* AST::identifier() {
    if (isType(Token::Word))
      return new Identifier(std::move(get(-1).value));

    return value();
  }
} // namespace wind::wdlang