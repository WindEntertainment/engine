#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::expression() {
    return binaryPriority0();
  }
} // namespace wind::wdlang