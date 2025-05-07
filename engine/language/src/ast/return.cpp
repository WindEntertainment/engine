#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::returnStatements() {
    if (isEqual(Token::Word, "return")) {
      Node* result = nullptr;
      if (!isEqual(Token::Operator, ";"))
        result = expression();

      auto* statement = new ReturnStatement();
      statement->value = result;

      return statement;
    }

    return assign();
  }
} // namespace wind::wdlang