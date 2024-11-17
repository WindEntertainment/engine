#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Div : public UIElement, public std::enable_shared_from_this<Div> {
  public:
    Div(unsigned int id, attributes::Div attributes);

    GET_PTR();
    ATTRIBUTES(Div, defaultDivAttributes);

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;
  };
} // namespace wind::dom
