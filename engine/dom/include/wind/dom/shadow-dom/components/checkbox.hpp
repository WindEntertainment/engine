#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Checkbox
      : public UIElementCRTP<Checkbox, dom::Checkbox, attributes::Checkbox>,
        public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox();
    Checkbox(const unsigned int id);

    // DEEP_COPY(Checkbox, attributes::Checkbox);
    GET_PTR(Checkbox);
    // COMPARE(Checkbox);
    // ATTRIBUTES(Checkbox, defaultCheckboxAttributes);

    // dom::UIElement::Ptr toReal() {};
    // void updateReal(dom::UIElement::Ptr element) {};
    // std::shared_ptr<attributes::Checkbox> mergeAttributes();
  };
} // namespace wind::dom::shadow
