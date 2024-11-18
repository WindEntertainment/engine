#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Select : public UIElementCRTP<Select, dom::Select, attributes::Select>,
                 public std::enable_shared_from_this<Select> {
  public:
    Select();
    Select(const unsigned int id);

    // DEEP_COPY(Select, attributes::Select);
    GET_PTR(Select);
    // COMPARE(Select);
    // ATTRIBUTES(Select, defaultSelectAttributes);

    // dom::UIElement::Ptr toReal() {};
    // void updateReal(dom::UIElement::Ptr element) {};
    // std::shared_ptr<attributes::Select> mergeAttributes();
  };
} // namespace wind::dom::shadow
