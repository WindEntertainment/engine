#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Select : public UIElement, public std::enable_shared_from_this<Select> {
  public:
    Select(unsigned int id, const attributes::Select& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Select> attributes;
  };

} // namespace wind::dom
