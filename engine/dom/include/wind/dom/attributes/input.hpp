#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Input;
};

namespace wind::dom::attributes {
  struct Input : public attributes::Base {
    bool tmp = {false};

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

    bool compare(const attributes::Base& attributes) override {
      const attributes::Input* attrs =
        dynamic_cast<const attributes::Input*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Input defaultInputAttributes = {};
} // namespace wind::dom::attributes
