#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include "wind/dom/attributes/index.hpp"
#include "wind/dom/utils/index.hpp"

namespace wind::dom {
#define ATTRIBUTES(attributesName, defaultAttributesName)                      \
  attributes::attributesName attributes = attributes::defaultAttributesName;   \
  attributes::attributesName hoverAttributes =                                 \
    attributes::defaultAttributesName;                                         \
  attributes::attributesName clickAttributes =                                 \
    attributes::defaultAttributesName;

#define GET_PTR()                                                              \
  Ptr getPtr() { return shared_from_this(); }
} // namespace wind::dom
