#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    GET_PTR();

    Text(unsigned int id, attributes::Text attributes);

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Text attributes = attributes::defaultTextAttributes;
  };

} // namespace wind::dom
