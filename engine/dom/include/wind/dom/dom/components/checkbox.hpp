#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {

  class Checkbox : public UIElement,
                   public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox(unsigned int id, attributes::Checkbox attributes);

    GET_PTR();
    ATTRIBUTES(Checkbox, defaultCheckboxAttributes);

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;
  };
} // namespace wind::dom
