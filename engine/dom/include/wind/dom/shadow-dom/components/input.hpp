#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Input : public UIElementCRTP<Input, dom::Input, attributes::Input>,
                public std::enable_shared_from_this<Input> {
  public:
    Input();
    Input(const unsigned int id);

    // DEEP_COPY(Input, attributes::Input);
    GET_PTR(Input);
    // COMPARE(Input);
    // ATTRIBUTES(Input, defaultInputAttributes);

    // dom::UIElement::Ptr toReal() {};
    // void updateReal(dom::UIElement::Ptr element) {};
    // std::shared_ptr<attributes::Input> mergeAttributes();
  };
} // namespace wind::dom::shadow
