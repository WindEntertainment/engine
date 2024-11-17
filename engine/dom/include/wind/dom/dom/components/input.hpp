#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {

  class Input : public UIElement, public std::enable_shared_from_this<Input> {
  public:
    Input(unsigned int id, attributes::Input attributes);

    GET_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Input attributes = attributes::defaultInputAttributes;
  };
} // namespace wind::dom
