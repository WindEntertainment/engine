#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Select : public UIElement, public std::enable_shared_from_this<Select> {
  public:
    Select();
    Select(const unsigned int id);

    DEEP_COPY(Select, attributes::Select);
    GET_PTR();
    COMPARE(Select);

    attributes::Select attributes = attributes::defaultSelectAttributes;
  };
} // namespace wind::dom::shadow
