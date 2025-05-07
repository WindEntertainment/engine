#pragma once
#include "Expression.hpp"

#include <string>

namespace wind::wdlang {
  struct Identifier : public Expression<Identifier> {
    std::string name;

    Identifier(std::string&& name) : name(name) {}
  };
} // namespace wind::wdlang
