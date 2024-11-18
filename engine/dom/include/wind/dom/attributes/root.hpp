#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom::attributes {
  struct Root : public attributes::Base {
    bool tmp = {false};

    bool compare(const std::shared_ptr<attributes::Base> attributes) override {
      const std::shared_ptr<attributes::Root> attrs =
        std::dynamic_pointer_cast<attributes::Root>(attributes);
      if (!attrs) {
        return false;
      }

      return std::tie(this->tmp) == std::tie(attrs->tmp);
    }
  };
  static const attributes::Root defaultRootAttributes = {};
} // namespace wind::dom::attributes
