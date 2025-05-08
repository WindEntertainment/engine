#include "wind/language/language.hpp"

namespace wind::wdlang {
  Node* AST::expression() {
    return binaryPriority0();
  }
} // namespace wind::wdlang