#include "wind/dom/dom/components/element.hpp"

namespace wind::dom {
  UIElement::UIElement(unsigned int id) : id(id) { children.reserve(3); }

  void UIElement::appendChild(Ptr child, Ptr parent) {
    if (child) {
      children.push_back(child);
      child->parent = parent;
      // child->root = root;
    }
  }

  void UIElement::display(wind::CommandBuffer& renderer) {
    update();
    render(renderer);
    for (const auto& child : children) {
      child->display(renderer);
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
} // namespace wind::dom
