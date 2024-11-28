#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Select;
};

namespace wind::dom::attributes {
  struct Select : public attributes::Base {
    bool tmp = {false};

    std::optional<std::function<void(std::shared_ptr<::wind::dom::Select>)>>
      onHover;
    std::optional<glm::vec4> backgroundColor;
    std::optional<std::shared_ptr<Texture>> texture;
    std::optional<float> angle;
    std::optional<float> borderRadius;
    std::optional<float> borderWidth;
    std::optional<glm::vec4> borderColor;
    std::optional<std::function<void(std::shared_ptr<::wind::dom::Select>)>>
      onClick;

    bool compare(const attributes::Base& attributes) override {
      const attributes::Select* attrs =
        dynamic_cast<const attributes::Select*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Select defaultSelectAttributes = {};
} // namespace wind::dom::attributes
