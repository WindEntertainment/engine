#include "wind/dom/shadow-dom/components/element.hpp"

namespace wind::dom::shadow {
  unsigned int UIElement::nextId = 0;

  UIElement::UIElement() : id(nextId++) { children.reserve(3); }
  UIElement::UIElement(unsigned int id) : id(id) { children.reserve(3); }

  void UIElement::appendChild(Ptr child) {
    if (child) {
      child->parent = this->getPtr();
      children.push_back(child);
      // child->root = root;
    }
  }

  void UIElement::removeChild(unsigned int childId) {
    auto it = std::ranges::find_if(children, [&](const Ptr& item) {
      return item->id == childId;
    });

    if (it == children.end())
      return;

    // (*it)->parent = nullptr;
    children.erase(it);
  };
} // namespace wind::dom::shadow
