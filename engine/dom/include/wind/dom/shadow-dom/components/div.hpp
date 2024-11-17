#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Div : public UIElement, public std::enable_shared_from_this<Div> {
  public:
    Div();
    Div(const unsigned int id);

    DEEP_COPY(Div, attributes::Div);
    GET_PTR();
    COMPARE(Div);
    ATTRIBUTES(Div, defaultDivAttributes);
  };
} // namespace wind::dom::shadow
