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

  template <typename T, typename... Args>
  void replaceOptionals(std::optional<T>& originalValue, Args&&... args) {
    ((args.has_value() && (originalValue = args.value())), ...);
  }

  template <typename T>
  static void replaceTuples(T& a, T& b, T& c) {
    constexpr size_t numFields = std::tuple_size_v<T>;

    [&]<std::size_t... FieldIndices>(std::index_sequence<FieldIndices...>) {
      ((utils::replaceOptionals(
         std::get<FieldIndices>(a),
         std::get<FieldIndices>(b),
         std::get<FieldIndices>(c)
       )),
       ...);
    }(std::make_index_sequence<numFields>{});
  }

} // namespace wind::dom::utils

namespace wind::dom::attributes {
  namespace options {
    enum class Display : std::int8_t { relative, flex, absolute };
    enum class Direction : std::int8_t { row, column };
    enum class Wrap : std::int8_t { wrap, noWrap };
    enum class JustifyContent : std::int8_t {
      start,
      end,
      center,
      spaceBetween,
      spaceAround
    };
    enum class AlignItems : std::int8_t {
      start,
      end,
      center,
    };
    enum class AlignContent : std::int8_t {
      start,
      end,
      center,
    };
  } // namespace options
  enum class Units : std::int8_t { percentage, pixel };

  struct ValueWithUnits {
    float value;
    Units units;

    bool operator==(const ValueWithUnits& item) const {
      return item.units == units && item.value == item.value;
    };
  };
} // namespace wind::dom::attributes

namespace wind::dom::shadow::attributes {
  namespace options {
    enum class Display : std::int8_t { relative, flex, absolute };
    enum class Direction : std::int8_t { row, column };
    enum class Wrap : std::int8_t { wrap, noWrap };
    enum class JustifyContent : std::int8_t {
      start,
      end,
      center,
      spaceBetween,
      spaceAround
    };
    enum class AlignItems : std::int8_t {
      start,
      end,
      center,
    };
    enum class AlignContent : std::int8_t {
      start,
      end,
      center,
    };
  } // namespace options
  enum class Units : std::int8_t { percentage, pixel };

  struct ValueWithUnits {
    float value;
    Units units;

    bool operator==(const ValueWithUnits& item) const {
      return item.units == units && item.value == item.value;
    };
  };
} // namespace wind::dom::shadow::attributes
