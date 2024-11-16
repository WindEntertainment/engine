#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Image : public attributes::Base {
    bool tmp = {false};

    bool compare(const attributes::Base& attributes) override {
      const attributes::Image* attrs =
        dynamic_cast<const attributes::Image*>(&attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Image defaultImageAttributes = {};
} // namespace wind::dom::attributes
