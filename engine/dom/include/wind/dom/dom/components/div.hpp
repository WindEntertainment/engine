#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Div : public UIElement, public std::enable_shared_from_this<Div> {
  public:
    Div(unsigned int id, const attributes::Div& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Div> attributes;
  };
} // namespace wind::dom
