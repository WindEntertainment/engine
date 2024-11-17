#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    Text(unsigned int id, attributes::Text attributes);

    GET_PTR();
    ATTRIBUTES(Text, defaultTextAttributes);

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;
  };

} // namespace wind::dom
