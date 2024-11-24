#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Select : public UIElement, public std::enable_shared_from_this<Select> {
  public:
    Select(unsigned int id, attributes::Select attributes);

    GET_REAL_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Select attributes = attributes::defaultSelectAttributes;
  };

} // namespace wind::dom
