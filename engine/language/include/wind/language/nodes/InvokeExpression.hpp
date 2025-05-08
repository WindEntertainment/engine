#pragma once
#include "Expression.hpp"

#include <list>
#include <string>

namespace wind::wdlang {
  struct InvokeExpression : public Expression<InvokeExpression> {
    Node* name;
    std::list<Node*> arguments;
  };
} // namespace wind::wdlang
