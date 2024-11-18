#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Div : public attributes::Base {
    bool tmp = {false};

    bool compare(const std::shared_ptr<attributes::Base> attributes) override {
      const std::shared_ptr<attributes::Div> attrs =
        std::dynamic_pointer_cast<attributes::Div>(attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Div defaultDivAttributes = {};
} // namespace wind::dom::attributes
