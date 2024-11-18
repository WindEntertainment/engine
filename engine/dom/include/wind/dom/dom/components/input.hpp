#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {

  class Input : public UIElement, public std::enable_shared_from_this<Input> {
  public:
    Input(unsigned int id, const attributes::Input& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Input> attributes;
  };
} // namespace wind::dom
