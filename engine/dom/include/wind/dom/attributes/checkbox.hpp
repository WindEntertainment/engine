#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Checkbox;
};

namespace wind::dom::attributes {
  struct Checkbox : public attributes::Base {
    bool tmp = {false};

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

    bool compare(const attributes::Base& attributes) override {
      const attributes::Checkbox* attrs =
        dynamic_cast<const attributes::Checkbox*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Checkbox defaultCheckboxAttributes = {};
} // namespace wind::dom::attributes
