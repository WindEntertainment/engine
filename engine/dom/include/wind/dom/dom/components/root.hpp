#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Root : public UIElement, public std::enable_shared_from_this<Root> {
  public:
    Root(unsigned int id, attributes::Root attributes);

    GET_PTR();
    ATTRIBUTES(Root, defaultRootAttributes);

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

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
} // namespace wind::dom
