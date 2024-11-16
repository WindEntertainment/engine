#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    Text();
    Text(const unsigned int id);

    DEEP_COPY(Text, attributes::Text);
    GET_PTR();
    COMPARE(Text);

    attributes::Text attributes = attributes::defaultTextAttributes;
  };
} // namespace wind::dom::shadow
