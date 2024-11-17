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
