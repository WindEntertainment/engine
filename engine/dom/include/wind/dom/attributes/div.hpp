#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Div;
};

namespace wind::dom::attributes {

  struct Div : public attributes::Base {
    // std::function<void(wind::dom::Div)> onClick = {};
    std::function<void(std::shared_ptr<::wind::dom::Div>)> onHover = {};

    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Div* attrs =
        dynamic_cast<const attributes::Div*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Div defaultDivAttributes = {};
} // namespace wind::dom::attributes
