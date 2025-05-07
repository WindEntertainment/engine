#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::assign() {
    if (isType(Token::Word) && isEqual(Token::Operator, "=")) {
      const auto name = get(-2).value;
      auto* value = expression();

      auto* statement = new AssignStatement();
      statement->name = name;
      statement->value = value;

      return statement;
    }

    shift();
    push("Syntax error: Unexpected symbol");
    return nullptr;
  }
} // namespace wind::wdlang