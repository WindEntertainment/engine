#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"

namespace wind::dom::utils {
  template <typename T>
  concept HasSize = requires(T t) {
    { t.position } -> std::convertible_to<glm::vec2>;
    { t.size } -> std::convertible_to<glm::vec2>;
  };

  template <HasSize T>
  static bool isHovered(std::shared_ptr<T> object) {
    auto context = wind::InputSystem::context;
    return context->mouseContext.cursorX > object->position.x &&
           context->mouseContext.cursorX <
             object->position.x + object->size.x &&
           context->mouseContext.cursorY > object->position.y &&
           context->mouseContext.cursorY < object->position.y + object->size.y;
  };

  template <HasSize T>
  static bool isClicked(std::shared_ptr<T> object, bool isHovered) {
    auto context = wind::InputSystem::context;
    return isHovered && context->key.action == KeyAction::Released &&
           context->key.keycode == Keycode::M_ButtonLeft;
  };

} // namespace wind::dom::utils
