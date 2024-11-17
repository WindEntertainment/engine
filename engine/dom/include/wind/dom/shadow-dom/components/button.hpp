#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Button : public UIElement, public std::enable_shared_from_this<Button> {
  public:
    Button();
    Button(const unsigned int id);

    DEEP_COPY(Button, attributes::Button);
    GET_PTR();
    COMPARE(Button);
    ATTRIBUTES(Button, defaultButtonAttributes);
  };
} // namespace wind::dom::shadow
