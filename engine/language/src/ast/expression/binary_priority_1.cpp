#include "wind/language/language.hpp"
#include "wind/language/nodes/BinaryOperation.hpp"

namespace wind::wdlang {
  Node* AST::binaryPriority1() {
    auto* result = binaryPriority2();

    if (result == nullptr)
      return nullptr;

    while (true) {
      if (auto [type, value] = get();
          type == Token::Operator &&
          (value == ">" || value == "<" || value == "==" || value == "!=" ||
           value == ">=" || value == "<=")) {
        shift();

        auto* binaryEx = new BinaryOperation();
        binaryEx->lhs = result;
        binaryEx->rhs = binaryPriority2();

        if (value == ">")
          binaryEx->type = BinaryOperation::Greater;
        else if (value == "<")
          binaryEx->type = BinaryOperation::Less;
        else if (value == "==")
          binaryEx->type = BinaryOperation::Equal;
        else if (value == "!=")
          binaryEx->type = BinaryOperation::NotEqual;
        else if (value == ">=")
          binaryEx->type = BinaryOperation::GreaterOrEqual;
        else if (value == "<=")
          binaryEx->type = BinaryOperation::LessOrEqual;

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