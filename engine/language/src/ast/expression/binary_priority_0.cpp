#include "wind/language/language.hpp"
#include "wind/language/nodes/BinaryOperation.hpp"

namespace wind::wdlang {
  Node* AST::binaryPriority0() {
    auto* result = binaryPriority1();

    if (result == nullptr)
      return nullptr;

    while (true) {
      if (auto [type, value] = get();
          type == Token::Operator && (value == "&&" || value == "||")) {
        shift();

        auto* binaryEx = new BinaryOperation();
        binaryEx->lhs = result;
        binaryEx->rhs = binaryPriority1();

        if (value == "&&")
          binaryEx->type = BinaryOperation::And;
        else if (value == "||")
          binaryEx->type = BinaryOperation::Or;

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