#include "wind/dom/dom/components/input.hpp"

namespace wind::dom {
  Input::Input(unsigned int id, attributes::Input attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Input::render(wind::CommandBuffer& renderer) {

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
      if (attributes.onHover.has_value()) {
        attributes.onHover.value()(getPtr());
      }
    }

    if (isClicked && attributes.onClick.has_value()) {
      attributes.onClick.value()(getPtr());
    }
  };
} // namespace wind::dom
