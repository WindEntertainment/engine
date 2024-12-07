#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/renderer/command-buffer.hpp"

namespace wind::dom {
  class Checkbox;
};

namespace wind::dom::attributes {
  struct Checkbox {
    std::optional<std::function<void()>> onChange;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Checkbox>)>>
      onHover;
    std::optional<glm::vec4> backgroundColor;
    std::optional<std::shared_ptr<Texture>> texture;
    std::optional<float> angle;
    std::optional<float> borderRadius;
    std::optional<float> borderWidth;
    std::optional<glm::vec4> borderColor;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Checkbox>)>>
      onClick;
    std::optional<glm::vec2> position;
    std::optional<glm::vec2> size;

    auto asTuple() const {
      return std::tie(
        backgroundColor,
        texture,
        angle,
        borderRadius,
        borderWidth,
        borderColor,
        position,
        size
      );
    }

    auto asMutableTuple() {
      return std::tie(
        backgroundColor,
        texture,
        angle,
        borderRadius,
        borderWidth,
        borderColor,
        position,
        size
      );
    }

    bool operator==(const attributes::Checkbox& element) {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultCheckboxAttributes = []() {
    auto attrs = attributes::Checkbox();
    attrs.position = {0, 0};
    return attrs;
  };
} // namespace wind::dom::attributes
