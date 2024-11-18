#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Checkbox : public attributes::Base {
    bool tmp = {false};

    std::function<void()> onChange;

    bool compare(const std::shared_ptr<attributes::Base> attributes) override {
      const std::shared_ptr<attributes::Checkbox> attrs =
        std::dynamic_pointer_cast<attributes::Checkbox>(attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Checkbox defaultCheckboxAttributes = {};
} // namespace wind::dom::attributes
