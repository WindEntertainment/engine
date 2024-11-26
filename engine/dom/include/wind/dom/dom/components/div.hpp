#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Div : public UIElement, public std::enable_shared_from_this<Div> {
  public:
    Div(unsigned int id, attributes::Div attributes);

    GET_REAL_PTR(Div);

    bool innerIsHovered = false;

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Div attributes = attributes::defaultDivAttributes;
  };
} // namespace wind::dom
