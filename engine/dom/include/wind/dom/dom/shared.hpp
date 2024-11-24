#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include "wind/dom/attributes/index.hpp"
#include "wind/dom/utils/index.hpp"

namespace wind::dom {
#define GET_REAL_PTR()                                                         \
  Ptr getPtr() { return shared_from_this(); }
} // namespace wind::dom
