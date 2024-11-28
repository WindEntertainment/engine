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

  template <typename T>
  static bool
  compareOptionals(const std::optional<T>& a, const std::optional<T>& b) {
    if (!a.has_value() && !b.has_value()) {
      return true;
    }

    if (!a.has_value() && b.has_value() || !b.has_value() && a.has_value()) {
      return false;
    }

    return a.value() == b.value();
  }

  template <typename T>
  static bool compareTuples(const T& a, const T& b) {
    constexpr size_t numFields = std::tuple_size_v<T>;

    return
      [&]<std::size_t... FieldIndices>(std::index_sequence<FieldIndices...>) {
        return (
          utils::compareOptionals(
            std::get<FieldIndices>(a), std::get<FieldIndices>(b)
          ) &&
          ...
        );
      }(std::make_index_sequence<numFields>{});
  }

} // namespace wind::dom::utils
