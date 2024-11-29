#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    Text(unsigned int id, attributes::Text attributes);

    GET_REAL_PTR(Text);

    bool innerIsHovered = false;
    std::shared_ptr<wind::TextMesh> mesh = std::make_shared<wind::TextMesh>();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    // void reset() override;

    attributes::Text attributes = attributes::getDefaultTextAttributes();
  };
} // namespace wind::dom
