#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Button : public UIElement, public std::enable_shared_from_this<Button> {
  public:
    Button(unsigned int id, attributes::Button attributes);

    GET_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Button attributes = attributes::defaultButtonAttributes;
  };
} // namespace wind::dom
