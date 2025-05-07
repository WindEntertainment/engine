#pragma once
#include "Expression.hpp"

namespace wind::wdlang {
  struct Value : public Expression<Value> {
    enum ValueType {
      Number,
      Char,
      String,
    };

    ValueType type;
    std::string value;
  };
} // namespace wind::wdlang
