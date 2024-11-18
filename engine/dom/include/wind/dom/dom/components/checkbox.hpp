#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {

  class Checkbox : public UIElement,
                   public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox(unsigned int id, const attributes::Checkbox& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Checkbox> attributes;
  };
} // namespace wind::dom
