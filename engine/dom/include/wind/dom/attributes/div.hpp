#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Div;
};

namespace wind::dom::attributes {

  struct Div : public attributes::Base {
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

    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Div* attrs =
        dynamic_cast<const attributes::Div*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }

    auto asTuple() { return std::tie(size, position); }
    // auto asTuple() { return std::tie(size, position); }
  };
  static const attributes::Div defaultDivAttributes = {};
} // namespace wind::dom::attributes
