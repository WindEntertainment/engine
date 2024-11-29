#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Checkbox : public UIElement,
                   public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox(unsigned int id, attributes::Checkbox attributes);

    GET_REAL_PTR(Checkbox);

    bool innerIsHovered = false;

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    // void reset() override;

    attributes::Checkbox attributes =
      attributes::getDefaultCheckboxAttributes();
  };
} // namespace wind::dom
