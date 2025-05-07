#pragma once
#include "NodeCRTP.hpp"

namespace wind::wdlang {
  template <typename Derived>
  struct Expression : public NodeCRTP<Derived> {};
} // namespace wind::wdlang
