#include "wind/dom/dom/components/checkbox.hpp"

namespace wind::dom {
  Checkbox::Checkbox(unsigned int id, attributes::Checkbox attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Checkbox::render(wind::CommandBuffer& renderer) {
    if (!attributes.position.has_value() || !attributes.size.has_value())
      return;

    renderer.drawRect(
      attributes.position.value(),
      attributes.size.value(),
      attributes.backgroundColor.value_or(glm::vec4{0.f, 0.f, 0.f, 1.f}),
      attributes.texture.value_or(nullptr),
      attributes.angle.value_or(0),
      attributes.borderRadius.value_or(0),
      attributes.borderWidth.value_or(0),
      attributes.borderColor.value_or(glm::vec4{0.f, 0.f, 0.f, 1.f})
    );
  };

  // void Checkbox::reset() {
  //   attributes = attributes::getDefaultCheckboxAttributes();
  // };

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
      if (attributes.onHover.has_value()) {
        attributes.onHover.value()(getPtr());
      }
    }

    if (isClicked && attributes.onClick.has_value()) {
      attributes.onClick.value()(getPtr());
    }
  };
} // namespace wind::dom
