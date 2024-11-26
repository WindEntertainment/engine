#pragma once
#include <wind/utils/utils.hpp>
#include "base.hpp"

namespace wind::dom {
  class Input;
};

namespace wind::dom::attributes {
  struct Input : public attributes::Base {
    bool tmp = {false};

    std::function<void(std::shared_ptr<::wind::dom::Input>)> onHover = {};

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
