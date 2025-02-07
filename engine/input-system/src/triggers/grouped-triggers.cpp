#include "wind/input-system/input-system.hpp"

#include "wind/input-system/context.hpp"
#include "wind/input-system/keys.hpp"
#include "wind/input-system/trigger.hpp"
#include "wind/utils/includes.hpp"
#include "wind/utils/utils.hpp"

namespace wind {

  void InputSystem::addGroupedTrigger(std::string groupName, Keys bindings) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->bindings.insert(
        bindings.begin(), bindings.end()
      );
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, bindings))
      );
    }
  }

  void InputSystem::addGroupedTrigger(std::string groupName, Key binding) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->bindings.insert(binding);
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, {binding}))
      );
    }
  }

  void InputSystem::addGroupedTrigger(
    std::string groupName,
    Keys bindings,
    Callbacks callbacks
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(
        callbacks.begin(), callbacks.end()
      );
      groupedTriggers[groupName]->bindings.insert(
        bindings.begin(), bindings.end()
      );
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, bindings, callbacks))
      );
    }
  }

  void InputSystem::addGroupedTrigger(
    std::string groupName,
    Keys bindings,
    Callback* callback
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(callback);
      groupedTriggers[groupName]->bindings.insert(
        bindings.begin(), bindings.end()
      );
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, bindings, {callback}))
      );
    }
  }

  void InputSystem::addGroupedTrigger(
    std::string groupName,
    Key binding,
    Callbacks callbacks
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(
        callbacks.begin(), callbacks.end()
      );
      groupedTriggers[groupName]->bindings.insert(binding);
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, {binding}, callbacks))
      );
    }
  }

  void InputSystem::addGroupedTrigger(
    std::string groupName,
    Key binding,
    Callback* callback
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(callback);
      groupedTriggers[groupName]->bindings.insert(binding);
    } else {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, {binding}, {callback}))
      );
    }
  }

  //

  void InputSystem::addGroupedTrigger(std::string groupName) {
    if (!groupedTriggers.contains(groupName)) {
      groupedTriggers.insert(
        std::make_pair(groupName, new Trigger(groupName, {}, {}))
      );
    }
  }

  void
  InputSystem::addGroupedTriggerBindings(std::string groupName, Key binding) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->bindings.insert(binding);
    }
  };

  void
  InputSystem::addGroupedTriggerBindings(std::string groupName, Keys bindings) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->bindings.insert(
        bindings.begin(), bindings.end()
      );
    }
  };

  //

  void InputSystem::addGroupedTriggerCallbacks(
    std::string groupName,
    Callback* callback
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(callback);
    }
  };

  void InputSystem::addGroupedTriggerCallbacks(
    std::string groupName,
    Callbacks callbacks
  ) {
    if (groupedTriggers.contains(groupName)) {
      groupedTriggers[groupName]->callbacks.insert(
        callbacks.begin(), callbacks.end()
      );
    }
  };

  //

} // namespace wind
