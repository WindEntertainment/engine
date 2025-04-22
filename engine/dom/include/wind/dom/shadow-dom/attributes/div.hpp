#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/renderer/command-buffer.hpp"
#include "wind/dom/dom/attributes/div.hpp"

namespace wind::dom {
  class Div;
} // namespace wind::dom

namespace wind::dom::shadow::attributes {

  struct Div {
    std::optional<glm::vec4> backgroundColor;
    std::optional<std::shared_ptr<Texture>> texture;
    std::optional<float> angle;
    std::optional<float> borderRadius;
    std::optional<float> borderWidth;
    std::optional<glm::vec4> borderColor;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Div>)>>
      onHover;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Div>)>>
      onClick;

    std::optional<ValueWithUnits> x;
    std::optional<ValueWithUnits> y;
    std::optional<ValueWithUnits> width;
    std::optional<ValueWithUnits> height;

    std::optional<options::Display> display;
    std::optional<options::Direction> flexDirection;
    std::optional<options::Wrap> wrap;
    std::optional<options::JustifyContent> justifyContent;
    std::optional<options::AlignItems> alignItems;
    std::optional<options::AlignContent> alignContent;
    std::optional<float> gap;

    [[nodiscard]] auto asTuple() const {
      return std::tie(
        backgroundColor,
        texture,
        angle,
        borderRadius,
        borderWidth,
        borderColor,
        x,
        y,
        width,
        height
      );
    }

    [[nodiscard]] auto asMutableTuple() {
      return std::tie(
        backgroundColor,
        texture,
        angle,
        borderRadius,
        borderWidth,
        borderColor,
        x,
        y,
        width,
        height
      );
    }

    bool operator==(const shadow::attributes::Div& element) const {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultDivAttributes = []() {
    auto attrs = shadow::attributes::Div();
    attrs.x = {.value = 0, .units = Units::pixel};
    attrs.y = {.value = 0, .units = Units::pixel};
    attrs.width = {.value = 0, .units = Units::pixel};
    attrs.height = {.value = 0, .units = Units::pixel};
    return attrs;
  };
} // namespace wind::dom::shadow::attributes
