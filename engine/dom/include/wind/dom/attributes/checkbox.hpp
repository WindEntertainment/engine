#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Checkbox;
};

namespace wind::dom::attributes {
  struct Checkbox : public attributes::Base {
    bool tmp = {false};

    std::function<void()> onChange;
    std::function<void(std::shared_ptr<::wind::dom::Checkbox>)> onHover = {};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Checkbox* attrs =
        dynamic_cast<const attributes::Checkbox*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Checkbox defaultCheckboxAttributes = {};
} // namespace wind::dom::attributes
