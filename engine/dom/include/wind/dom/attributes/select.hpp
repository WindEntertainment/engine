#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Select : public attributes::Base {
    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Select* attrs =
        dynamic_cast<const attributes::Select*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Select defaultSelectAttributes = {};
} // namespace wind::dom::attributes
