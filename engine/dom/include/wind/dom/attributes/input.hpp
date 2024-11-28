#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/renderer/command-buffer.hpp"

namespace wind::dom {
  class Input;
};

namespace wind::dom::attributes {
  struct Input {
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Input>)>>
      onHover;
    std::optional<glm::vec4> backgroundColor;
    std::optional<std::shared_ptr<Texture>> texture;
    std::optional<float> angle;
    std::optional<float> borderRadius;
    std::optional<float> borderWidth;
    std::optional<glm::vec4> borderColor;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Input>)>>
      onClick;
    std::optional<glm::vec2> position;
    std::optional<glm::vec2> size;
    bool isHovered = false;

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

    bool operator==(const attributes::Input& element) {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultInputAttributes = []() {
    auto attrs = attributes::Input();
    attrs.position = {0, 0};
    return attrs;
  };
} // namespace wind::dom::attributes
