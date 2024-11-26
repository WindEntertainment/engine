#pragma once
#include "wind/dom/attributes/index.hpp"
#include "wind/dom/utils/index.hpp"

namespace wind::dom {
#define GET_REAL_PTR(className)                                                \
  std::shared_ptr<className> getPtr() { return shared_from_this(); }
} // namespace wind::dom
