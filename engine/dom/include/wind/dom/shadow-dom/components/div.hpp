#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Div : public UIElement<Div, dom::Div, attributes::Div>,
              public std::enable_shared_from_this<Div> {
  public:
    Div();
    Div(const unsigned int id);

    // DEEP_COPY(Div, attributes::Div);
    GET_PTR(Div);
    // COMPARE(Div);
    // ATTRIBUTES(Div, defaultDivAttributes);

    // dom::UIElement::Ptr toReal() {};
    // void updateReal(dom::UIElement::Ptr element) {};

    // std::shared_ptr<attributes::Div> mergeAttributes();
  };
} // namespace wind::dom::shadow
