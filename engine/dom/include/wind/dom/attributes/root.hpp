#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Root;
};

namespace wind::dom::attributes {
  struct Root : public attributes::Base {
    bool tmp = {false};

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

    bool compare(const attributes::Base& attributes) override {
      const attributes::Root* attrs =
        dynamic_cast<const attributes::Root*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Root defaultRootAttributes = {};
} // namespace wind::dom::attributes
