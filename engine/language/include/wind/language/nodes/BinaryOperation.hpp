#pragma once
#include "Expression.hpp"

namespace wind::wdlang {
  struct BinaryOperation : public Expression<BinaryOperation> {
    enum OperationType {
      Add,
      Sub,
      Mul,
      Div,
      Equal,
      NotEqual,
      Greater,
      Less,
      GreaterOrEqual,
      LessOrEqual,
      And,
      Or
    };

    OperationType type;
    Node* lhs;
    Node* rhs;
  };
} // namespace wind::wdlang
