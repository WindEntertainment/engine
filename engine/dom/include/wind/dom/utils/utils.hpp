#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"

namespace wind::dom::utils {
  template <typename T>
  concept HasSize = requires(T t) {
    { t.position } -> std::convertible_to<std::optional<glm::vec2>>;
    { t.size } -> std::convertible_to<std::optional<glm::vec2>>;
  };

  template <HasSize T>
  static bool isHovered(T object) {
    if (!object.position.has_value() || !object.size.has_value())
      return false;

    auto pos = object.position.value();
    auto size = object.size.value();

    auto context = wind::InputSystem::context;
    return context->mouseContext.cursorX > pos.x &&
           context->mouseContext.cursorX < pos.x + size.x &&
           context->mouseContext.cursorY > pos.y &&
           context->mouseContext.cursorY < pos.y + size.y;
  };

  template <HasSize T>
  static bool isClicked(T object, bool isHovered) {
    auto context = wind::InputSystem::context;
    return isHovered && context->key.action == KeyAction::Released &&
           context->key.keycode == Keycode::M_ButtonLeft;
  }

} // namespace wind::dom::utils
