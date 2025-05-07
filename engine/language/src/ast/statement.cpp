#include "wind/language/language.hpp"

namespace wind::wdlang {

  inline void AST::parse() {
    while (get(0).type != Token::T_EOF) {
      currentScope = Scope::Global;
      ast.emplace_back(statement());
    }
  }

  inline Node* AST::statement() {
    return classes();
  }

} // namespace wind::wdlang