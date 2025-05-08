#pragma once
#include "Expression.hpp"

#include <string>

namespace wind::wdlang {
  struct Identifier : public Expression<Identifier> {
    std::list<std::string> path;
  };
} // namespace wind::wdlang
