#include "wind/dom/dom/components/input.hpp"

namespace wind::dom {
  Input::Input(unsigned int id, attributes::Input attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Input::render(wind::CommandBuffer& renderer) {
    renderer.drawRect(
      attributes.position,
      attributes.size,
      attributes.backgroundColor,
      attributes.texture,
      attributes.angle,
      attributes.borderRadius,
      attributes.borderWidth,
      attributes.borderColor
    );
  };

  void Input::reset() { attributes = attributes::defaultInputAttributes; };

  void Input::update() {
    auto context = wind::InputSystem::context;
    auto isHovered = utils::isHovered(attributes);
    auto isClicked = utils::isClicked(attributes, isHovered);

    if (!isHovered && innerIsHovered) {
      innerIsHovered = false;
    }

    // if (isHovered && attributes.onHover) {
    //   attributes.onHover();
    // }

    if (isHovered && !innerIsHovered) {
      innerIsHovered = true;
      if (attributes.onHover) {
        attributes.onHover(getPtr());
      }
    }

    if (isClicked && attributes.onClick) {
      attributes.onClick();
    }
  };
} // namespace wind::dom
