#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Text;
};

namespace wind::dom::attributes {
  struct Text : public attributes::Base {
    bool tmp = {false};

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

    bool compare(const attributes::Base& attributes) override {
      const attributes::Text* attrs =
        dynamic_cast<const attributes::Text*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Text defaultTextAttributes = {};
} // namespace wind::dom::attributes
