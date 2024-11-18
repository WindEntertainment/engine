#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Button : public UIElement, public std::enable_shared_from_this<Button> {
  public:
    Button(unsigned int id, const attributes::Button& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Button> attributes;
  };
} // namespace wind::dom
