#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/renderer/command-buffer.hpp"

namespace wind::dom {
  class Text;
};

namespace wind::dom::attributes {
  struct Text {
    std::optional<std::shared_ptr<Font>> font;
    std::optional<int> letterSpacing;
    std::optional<int> lineSpacing;
    std::optional<int> lineWidth;
    std::optional<std::string> value;
    std::optional<glm::vec2> scale;
    std::optional<glm::vec4> color;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Text>)>>
      onHover;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Text>)>>
      onClick;
    std::optional<glm::vec2> position;
    std::optional<glm::vec2> size;

    auto asTuple() const {
      return std::tie(
        font,
        letterSpacing,
        lineSpacing,
        lineWidth,
        value,
        scale,
        color,
        position,
        size
      );
    }

    auto asMutableTuple() {
      return std::tie(
        font,
        letterSpacing,
        lineSpacing,
        lineWidth,
        value,
        scale,
        color,
        position,
        size
      );
    }

    bool operator==(const attributes::Text& element) {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultTextAttributes = []() {
    auto attrs = attributes::Text();
    attrs.position = {0, 0};
    attrs.letterSpacing = 0;
    attrs.lineSpacing = 12;
    attrs.lineWidth = 250;
    return attrs;
  };
} // namespace wind::dom::attributes
