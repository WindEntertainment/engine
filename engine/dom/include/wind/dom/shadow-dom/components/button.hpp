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

// #pragma once
// #include <wind/dom/shadow-dom/shared.hpp>
// #include "element.hpp"

// namespace wind::dom::shadow {
//   class Button : public UIElementCRTP<Button, dom::Button,
//   attributes::Button>,
//                  public std::enable_shared_from_this<Button> {
//   public:
//     Button();
//     Button(const unsigned int id);

//     // DEEP_COPY(Button, attributes::Button);
//     // GET_PTR(Button);
//     // COMPARE(Button);
//     // ATTRIBUTES(Button, defaultButtonAttributes);

//     bool operator==(UIElement& elementReference) override {
//       Button* element = dynamic_cast<Button*>(&elementReference);
//       if (!element)
//         return false;
//       return attributes == element->attributes;
//     }

//     std::shared_ptr<Button> getPtr() { return shared_from_this(); }

//     std::shared_ptr<Button> deepCopy() override {
//       auto element = wind::share(Button(this->id));
//       // element->attributes = attributes::Button(this->attributes);
//       for (auto&& child : this->children) {
//         // element->appendChild(child->deepCopy());
//       };
//       return element;
//     };

//     std::shared_ptr<dom::UIElement> toReal() {};
//     void updateReal(std::shared_ptr<dom::Button> element) {};
//     std::shared_ptr<attributes::Button> mergeAttributes() {};
//   };
// } // namespace wind::dom::shadow
