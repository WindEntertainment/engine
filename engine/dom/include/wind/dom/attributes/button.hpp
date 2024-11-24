#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Button : public attributes::Base {
    // std::function<void(wind::dom::Button)> onClick = {};
    // std::function<void(wind::dom::Button)> onHover = {};

    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Button* attrs =
        dynamic_cast<const attributes::Button*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Button defaultButtonAttributes = {};
} // namespace wind::dom::attributes
