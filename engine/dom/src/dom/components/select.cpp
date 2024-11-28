#include "wind/dom/dom/components/select.hpp"

namespace wind::dom {
  Select::Select(unsigned int id, attributes::Select attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Select::render(wind::CommandBuffer& renderer) {};

  void Select::reset() { attributes = attributes::defaultSelectAttributes; };

  void Select::update() {
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
