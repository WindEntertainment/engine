#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Text;
};

namespace wind::dom::attributes {
  struct Text : public attributes::Base {
    bool tmp = {false};

    std::function<void(std::shared_ptr<::wind::dom::Text>)> onHover = {};

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
