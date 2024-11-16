#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Input : public UIElement, public std::enable_shared_from_this<Input> {
  public:
    Input();
    Input(const unsigned int id);

    DEEP_COPY(Input, attributes::Input);
    GET_PTR();
    COMPARE(Input);

    attributes::Input attributes = attributes::defaultInputAttributes;
  };
} // namespace wind::dom::shadow
