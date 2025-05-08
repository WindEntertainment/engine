#include "wind/language/language.hpp"
#include "wind/language/nodes/BinaryOperation.hpp"

namespace wind::wdlang {
  Node* AST::binaryPriority3() {
    auto* result = parentheses();

    if (result == nullptr)
      return nullptr;

    while (true) {
      if (auto [type, value] = get();
          type == Token::Operator && (value == "*" || value == "/")) {
        shift();

        auto* binaryEx = new BinaryOperation();
        binaryEx->lhs = result;
        binaryEx->rhs = parentheses();

        if (value == "*")
          binaryEx->type = BinaryOperation::Mul;
        else if (value == "/")
          binaryEx->type = BinaryOperation::Div;

        if (binaryEx->rhs == nullptr) {
          push(
            "Syntax Error: Unexpected symbol. Excepted expression to "
            "binary operation"
          );
          return nullptr;
        }

        result = binaryEx;
          } else
            break;
    }

    return result;
  }
} // namespace wind::wdlang