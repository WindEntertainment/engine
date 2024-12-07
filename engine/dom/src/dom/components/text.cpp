#include "wind/dom/dom/components/text.hpp"
#include "wind/renderer/procedural-graphics.hpp"

namespace wind::dom {
  Text::Text(unsigned int id, attributes::Text attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Text::render(wind::CommandBuffer& renderer) {
    if (!attributes.font.has_value())
      return;

    mesh->font = attributes.font.value();
    mesh->letterSpacing = attributes.letterSpacing.value_or(0);
    mesh->lineSpacing = attributes.lineSpacing.value_or(12);
    mesh->lineWidth = attributes.lineWidth.value_or(250);
    mesh->setText(attributes.value.value_or(""));

    renderer.drawText(
      mesh,
      attributes.position.value_or(glm::vec2{0, 0}),
      attributes.scale.value_or(glm::vec2{1.f, 1.f}),
      attributes.color.value_or(glm::vec4{0.f, 0.f, 0.f, 1.f})
    );
  };

  // void Text::reset() { attributes = attributes::getDefaultTextAttributes(); };

  void Text::update() {
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
