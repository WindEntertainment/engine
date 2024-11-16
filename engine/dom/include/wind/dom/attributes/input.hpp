#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Input : public attributes::Base {
    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Input* attrs =
        dynamic_cast<const attributes::Input*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Input defaultInputAttributes = {};
} // namespace wind::dom::attributes
