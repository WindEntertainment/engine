#include "wind/language/language.hpp"
#include "wind/language/nodes/UnaryOperation.hpp"

namespace wind::wdlang {
  Node* AST::unary() {
    if (isEqual(Token::Operator, "-")) {
      auto* unaryEx = new UnaryOperation();
      unaryEx->type = UnaryOperation::NEGATE;
      unaryEx->operand = expression();

      if (unaryEx->operand != nullptr)
        return unaryEx;

      push("Syntax Error: Unexpected symbol. Excepted expression to negate");
      delete unaryEx;
      return nullptr;
    }

    return identifier();
  }
} // namespace wind::wdlang