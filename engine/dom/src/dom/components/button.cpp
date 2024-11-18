#include "wind/dom/dom/components/button.hpp"

namespace wind::dom {
  Button::Button(unsigned int id, const attributes::Button& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Button>(attributes)) {};

  void Button::render(wind::CommandBuffer& renderer) {
    renderer.drawRect(
      attributes->position,
      attributes->size,
      attributes->backgroundColor,
      attributes->texture,
      attributes->angle,
      attributes->borderRadius,
      attributes->borderWidth,
      attributes->borderColor
    );
  };

  void Button::update() {
    auto context = wind::InputSystem::context;
    auto isHovered = utils::isHovered(attributes);
    auto isClicked = utils::isClicked(attributes, isHovered);

    if (!isHovered && attributes->isHovered) {
      attributes->isHovered = false;
    }

    if (isHovered && !attributes->isHovered) {
      attributes->isHovered = true;
      if (attributes->onHover) {
        attributes->onHover();
      }
    }

    if (isClicked && attributes->onClick) {
      attributes->onClick();
    }
  };
} // namespace wind::dom
