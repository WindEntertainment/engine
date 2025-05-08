#include "wind/language/language.hpp"
#include "wind/language/nodes/ImportStatement.hpp"

namespace wind::wdlang {
  Node* AST::imports() {
    if (isEqual(Token::Word, "import")) {
      Node* path = identifier(true);
      if (!path) {
        push("Syntax Error: Expect import path");
        return nullptr;
      }

      if (currentScope == Scope::Imports) {
        auto* statement = new ImportStatement();
        statement->path = path;
        return statement;
      }

      shift();
      push(
        "Syntax Error: imports may be only as first statements in file"
      );
      return nullptr;
    }

    currentScope = Scope::Global;
    return classes();
  }
}