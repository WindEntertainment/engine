#pragma once
#include <wind/dom/dom/shared.hpp>
#include "element.hpp"

namespace wind::dom {
  class Image : public UIElement, public std::enable_shared_from_this<Image> {
  public:
    Image(unsigned int id, attributes::Image attributes);

    GET_PTR();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    attributes::Image attributes = attributes::defaultImageAttributes;
  };
} // namespace wind::dom
