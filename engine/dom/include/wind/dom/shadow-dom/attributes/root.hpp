#pragma once
#include "wind/dom/utils/index.hpp"
#include "wind/renderer/command-buffer.hpp"
#include "wind/dom/dom/attributes/root.hpp"

namespace wind::dom::shadow::attributes {
  struct Root {
    std::optional<glm::vec4> backgroundColor;
    std::optional<std::shared_ptr<Texture>> texture;
    std::optional<float> angle;
    std::optional<float> borderRadius;
    std::optional<float> borderWidth;
    std::optional<glm::vec4> borderColor;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Root>)>>
      onHover;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Root>)>>
      onClick;
    std::optional<ValueWithUnits> x;
    std::optional<ValueWithUnits> y;
    std::optional<ValueWithUnits> width;
    std::optional<ValueWithUnits> height;

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

    bool operator==(const shadow::attributes::Root& element) const {
      auto a = asTuple();
      auto b = element.asTuple();

      return utils::compareTuples(a, b);
    };
  };

  static auto getDefaultRootAttributes = []() {
    auto attrs = shadow::attributes::Root();
    attrs.x = {.value = 0, .units = Units::pixel};
    attrs.y = {.value = 0, .units = Units::pixel};
    attrs.width = {.value = 0, .units = Units::pixel};
    attrs.height = {.value = 0, .units = Units::pixel};
    return attrs;
  };
} // namespace wind::dom::shadow::attributes
