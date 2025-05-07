#pragma once
#include "../LangImpl.hpp"

namespace wind::wdlang {
  struct Node {
    virtual ~Node() = default;
    virtual void execute(LangImpl*) = 0;
  };
} // namespace wind::wdlang
