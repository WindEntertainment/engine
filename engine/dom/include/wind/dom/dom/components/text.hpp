#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    Text(unsigned int id, const attributes::Text& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Text> attributes;
  };

} // namespace wind::dom
