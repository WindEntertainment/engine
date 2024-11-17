#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include "wind/dom/attributes/index.hpp"
#include "wind/dom/utils/index.hpp"

namespace wind::dom::shadow {
#define ATTRIBUTES(attributesName, defaultAttributesName)                      \
  attributes::attributesName attributes = attributes::defaultAttributesName;   \
  attributes::attributesName hoverAttributes =                                 \
    attributes::defaultAttributesName;                                         \
  attributes::attributesName clickAttributes =                                 \
    attributes::defaultAttributesName;

#define COMPARE(className)                                                     \
  bool operator==(UIElement& elementReference) override {                      \
    className* element = dynamic_cast<className*>(&elementReference);          \
    if (!element)                                                              \
      return false;                                                            \
    return attributes == element->attributes;                                  \
  }

#define GET_PTR()                                                              \
  Ptr getPtr() { return shared_from_this(); }

#define DEEP_COPY(className, attributesName)                                   \
  Ptr deepCopy() override {                                                    \
    auto element = wind::share(className(this->id));                           \
    element->attributes = attributesName(this->attributes);                    \
    for (auto&& child : this->children) {                                      \
      element->appendChild(child->deepCopy());                                 \
    };                                                                         \
    return element;                                                            \
  };
} // namespace wind::dom::shadow
