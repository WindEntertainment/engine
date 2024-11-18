#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Root : public UIElement, public std::enable_shared_from_this<Root> {
  public:
    Root();
    Root(const unsigned int id);

    DEEP_COPY(Root, attributes::Root);
    GET_PTR();
    COMPARE(Root);
    ATTRIBUTES(Root, defaultRootAttributes);

    UIElement::Ptr
    findElementById(const UIElement::Ptr& root, const unsigned int& id) {
      if (!root)
        return nullptr;

      if (root->id == id)
        return root;

      for (const auto& child : root->children) {
        auto result = findElementById(child, id);
        if (result)
          return result;
      }

      return nullptr;
    }
  };
} // namespace wind::dom::shadow

// #pragma once
// #include <wind/dom/shadow-dom/shared.hpp>
// #include "element.hpp"

// namespace wind::dom::shadow {
//   class Root : public UIElementCRTP<Root, dom::Root, attributes::Root>,
//                public std::enable_shared_from_this<Root> {
//   public:
//     Root();
//     Root(const unsigned int id);

//     // DEEP_COPY(Root, attributes::Root);
//     // GET_PTR(Root);
//     // COMPARE(Root);
//     // ATTRIBUTES(Root, defaultRootAttributes);

//     std::shared_ptr<shadow::UIElement> findElementById(
//       const std::shared_ptr<shadow::UIElement> root,
//       const unsigned int& id
//     ) {
//       if (!root)
//         return nullptr;

//       if (root->id == id)
//         return root;

//       for (const auto& child : root->children) {
//         auto result = findElementById(child, id);
//         if (result)
//           return result;
//       }

//       return nullptr;
//     }

//     // dom::UIElement::Ptr toReal() {};
//     // void updateReal(dom::UIElement::Ptr element) {};
//     // std::shared_ptr<attributes::Root> mergeAttributes();

//     bool operator==(UIElement& elementReference) override {
//       Root* element = dynamic_cast<Root*>(&elementReference);
//       if (!element)
//         return false;
//       return attributes == element->attributes;
//     }

//     std::shared_ptr<Root> getPtr() { return shared_from_this(); }

//     std::shared_ptr<Root> deepCopy() override {
//       auto element = wind::share(Root(this->id));
//       // element->attributes = attributes::Root(this->attributes);
//       for (auto&& child : this->children) {
//         // element->appendChild(child->deepCopy());
//       };
//       return element;
//     };

//     std::shared_ptr<dom::UIElement> toReal() {};
//     void updateReal(std::shared_ptr<dom::Root> element) {};
//     std::shared_ptr<attributes::Root> mergeAttributes() {};
//   };
// } // namespace wind::dom::shadow
