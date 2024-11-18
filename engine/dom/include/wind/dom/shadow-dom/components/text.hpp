#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Text : public UIElementCRTP<Text, dom::Text, attributes::Text>,
               public std::enable_shared_from_this<Text> {
  public:
    Text();
    Text(const unsigned int id);

    // DEEP_COPY(Text, attributes::Text);
    GET_PTR(Text);
    // COMPARE(Text);
    // ATTRIBUTES(Text, defaultTextAttributes);
    // TO_REAL(Text);
    // dom::UIElement::Ptr toReal() {
    //   return wind::share(wind::dom::Checkbox(this -> id, this->attributes))
    // };
    // void updateReal(dom::UIElement::Ptr element) {};
    // std::shared_ptr<attributes::Text> mergeAttributes() override {}
  };
} // namespace wind::dom::shadow
