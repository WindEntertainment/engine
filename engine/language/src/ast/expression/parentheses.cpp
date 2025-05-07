#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::parentheses() {
    if (isEqual(Token::Operator, "(")) {
      auto* result = expression();
      if (!isEqual(Token::Operator, ")")) {
        shift();
        push(
          "Syntax Error: Unmatched opening parenthesis '(' detected. "
          "Ensure every '(' has a corresponding ')' before the end of the "
          "expression.)"
        );
        return nullptr;
      }

      return result;
    }

    return unary();
  }
} // namespace wind::wdlang