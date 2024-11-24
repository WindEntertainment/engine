#include "wind/dom/shadow-dom/components/element.hpp"

namespace wind::dom::shadow {
  void appendChild(Button& child, Element& parent) {
    child.tree->parent = parent;
    std::visit(
      [&child](auto& element) { element.tree->children.push_back(child); },
      parent
    );
    // parent.tree->children.push_back(child);
  };
  void appendChild(Root& child, Element& parent) {
    child.tree->parent = parent;
    std::visit(
      [&child](auto& element) { element.tree->children.push_back(child); },
      parent
    );
    // parent.tree->children.push_back(child);
  };
  void removeChild(unsigned int childId, Element& parent) {
    std::visit(
      [&childId](auto& element) {
        auto it = std::ranges::find_if(
          element.tree->children,
          [&](const Element& childVariant) {
            return std::visit(
              [&childId](auto& child) { return child.id == childId; },
              childVariant
            );
          }
        );

        if (it == element.tree->children.end())
          return;

        // (*it).tree->parent = std::nullopt;
        element.tree->children.erase(it);
      },
      parent
    );
  };

  attributes::Root mergeAttributes(Root& shadow) { return shadow.attributes; };
  attributes::Button mergeAttributes(Button& shadow) {
    return shadow.attributes;
  };

  std::shared_ptr<dom::Root> toReal(Root& shadow) {
    return wind::share(dom::Root(shadow.id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Button> toReal(Button& shadow) {
    return wind::share(dom::Button(shadow.id, mergeAttributes(shadow)));
  };

  void updateReal(std::shared_ptr<dom::Root> real, Root& shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  void updateReal(std::shared_ptr<dom::Button> real, Button& shadow) {
    // spdlog::info("X: {}", shadow.attributes.backgroundColor.x);
    real->attributes = mergeAttributes(shadow);
  };

  Button::Button() : id(++nextId) {};
  Button::Button(unsigned int id) : id(id) {};
  Root::Root() : id(++nextId) {};
  Root::Root(unsigned int id) : id(id) {};

  // Element::Element(const ElementVariants& item) : item(item), id(++nextId) {
  //   children.reserve(3);
  // }

  // Element::Element(const Element& element)
  //     : item(element.item), id(element.id), children(element.children),
  //       parent(element.parent) {
  //   children.reserve(3);
  // }

  // bool Element::operator==(const Element& element) {};

  // void Element::appendChild(Element& child) {
  //   child.parent = this;
  //   children.push_back(child);
  //   // std::visit(
  //   //   [this](const auto& child) -> std::string {
  //   //     // if (child) {
  //   //     using T = std::decay_t<decltype(child)>;
  //   //     if constexpr (!std::is_same_v<T, std::monostate>) {
  //   //       // child->parent = this->getPtr();
  //   //       // children.push_back(child);
  //   //       return "EMPTY";
  //   //     };
  //   //     // child->root = root;
  //   //     // }
  //   //   },
  //   //   child
  //   // );
  // };

  // void Element::removeChild(unsigned int childId) {
  // auto it = std::ranges::find_if(children, [&](const Element& item) {
  // return item->id == childId;
  // return true;
  // });

  // if (it == children.end())
  //   return;

  // // (*it)->parent = nullptr;
  // children.erase(it);
  // };

  // Element Element::deepCopy() {
  //   Element element = Element(this->item);
  //   // element.attributes = this->attributes;
  //   // for (const E& child : this->children) {};
  //   return element;
  // };

}; // namespace wind::dom::shadow
// unsigned int UIElement::nextId = 0;
// template <typename S, typename R, typename A>
// unsigned int UIElement<S, R, A>::nextId = 0;

// UIElement::UIElement() : id(nextId++) { children.reserve(3); }
// UIElement::UIElement(unsigned int id) : id(id) { children.reserve(3); }

// void UIElement::appendChild(std::shared_ptr<UIElement> child) {
//   if (child) {
//     // child->parent = this->getPtr();
//     children.push_back(child);
//     // child->root = root;
//   }
// }

// void UIElement::removeChild(unsigned int childId) {
//   auto it = std::ranges::find_if(
//     children,
//     [&](const std::shared_ptr<UIElement>& item) {
//       return item->id == childId;
//     }
//   );

//   if (it == children.end())
//     return;

//   // (*it)->parent = nullptr;
//   children.erase(it);
// };
// } // namespace wind::dom::shadow
