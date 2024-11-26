#include "wind/dom/dom/components/checkbox.hpp"

namespace wind::dom {
  Checkbox::Checkbox(unsigned int id, attributes::Checkbox attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Checkbox::render(wind::CommandBuffer& renderer) {
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

  void Checkbox::reset() {
    attributes = attributes::defaultCheckboxAttributes;
  };

  void Checkbox::update() {
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
