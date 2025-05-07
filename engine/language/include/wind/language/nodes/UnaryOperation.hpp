#pragma once
#include "Expression.hpp"

namespace wind::wdlang {
  struct UnaryOperation : public Expression<UnaryOperation> {
    enum OperationType {
      NEGATE
    };

    OperationType type;
    Node* operand;
  };
} // namespace wind::wdlang
