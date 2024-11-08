#pragma once
#include "wind/input-system/context.hpp"
#include "wind/input-system/keys.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <set>

namespace wind {
  using Callback = std::function<void(std::shared_ptr<InputSystemContext>)>;
  using Callbacks = std::set<Callback*>;

  struct Trigger {
    std::string name;
    Keys bindings;
    Callbacks callbacks;

    Trigger(
      std::string name,
      const Keys bindings = {},
      const Callbacks callbacks = {}
    );
  };

} // namespace wind
