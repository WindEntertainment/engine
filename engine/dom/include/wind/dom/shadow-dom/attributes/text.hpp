#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/dom/dom/attributes/text.hpp"
#include "wind/renderer/command-buffer.hpp"

namespace wind::dom::shadow::attributes {
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
    std::optional<ValueWithUnits> x;
    std::optional<ValueWithUnits> y;
    std::optional<ValueWithUnits> width;
    std::optional<ValueWithUnits> height;

    [[nodiscard]] auto asTuple() const {
      return std::tie(
        font,
        letterSpacing,
        lineSpacing,
        lineWidth,
        value,
        scale,
        color,
        x,
        y,
        width,
        height
      );
    }

    [[nodiscard]] auto asMutableTuple() {
      return std::tie(
        font,
        letterSpacing,
        lineSpacing,
        lineWidth,
        value,
        scale,
        color,
        x,
        y,
        width,
        height
      );
    }

    bool operator==(const shadow::attributes::Text& element) const {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultTextAttributes = []() {
    auto attrs = shadow::attributes::Text();
    attrs.x = {.value = 0, .units = Units::pixel};
    attrs.y = {.value = 0, .units = Units::pixel};
    attrs.width = {.value = 0, .units = Units::pixel};
    attrs.height = {.value = 0, .units = Units::pixel};
    attrs.letterSpacing = 0;
    attrs.lineSpacing = 12;
    attrs.lineWidth = 250;
    return attrs;
  };
} // namespace wind::dom::shadow::attributes
