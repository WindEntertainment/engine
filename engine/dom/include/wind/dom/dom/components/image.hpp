#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Image : public UIElement, public std::enable_shared_from_this<Image> {
  public:
    Image(unsigned int id, const attributes::Image& attributes);

    GET_ELEMENT_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;

    std::shared_ptr<attributes::Image> attributes;
  };
} // namespace wind::dom
