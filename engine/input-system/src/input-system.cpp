#include "wind/input-system/input-system.hpp"
#include "wind/input-system/context.hpp"
#include "wind/input-system/error.hpp"
#include "wind/input-system/keys.hpp"
#include "wind/input-system/trigger.hpp"
#include "wind/utils/includes.hpp"
#include "wind/utils/utils.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

#include <wind/asset-pipeline/asset-manager.hpp>

namespace wind {

  std::unordered_map<Key, Callbacks, KeyHash> InputSystem::keycodeTriggers;
  std::map<std::string, Trigger*> InputSystem::groupedTriggers;

  InputSystemContext* InputSystem::context = new InputSystemContext();

  inline void InputSystem::groupedEventToCycle(Key keycode) {
    if (keycodeTriggers.contains(keycode)) {
      std::for_each(
        keycodeTriggers[keycode].begin(),
        keycodeTriggers[keycode].end(),
        [](Callback* callback) { (*callback)(context); }
      );
    }
  }

  // void InputSystem::init(GLFWwindow* window) {
  //   glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
  //   int action, int mods) {
  //     auto mappedKey = mapGlfwKeyboardCodeToKey(key, action);

  //     switch (mappedKey.action) {
  //     case KeyAction::Pressed:
  //       context->keyboardContext.addPressedKey(mappedKey.keycode);
  //       context->keyboardContext.removeHeldKey(mappedKey.keycode);
  //       context->keyboardContext.removeReleasedKey(mappedKey.keycode);
  //       break;

  //     case KeyAction::Held:
  //       context->keyboardContext.addHeldKey(mappedKey.keycode);
  //       context->keyboardContext.removePressedKey(mappedKey.keycode);
  //       context->keyboardContext.removeReleasedKey(mappedKey.keycode);
  //       break;

  //     case KeyAction::Released:
  //       context->keyboardContext.addReleasedKey(mappedKey.keycode);
  //       context->keyboardContext.removePressedKey(mappedKey.keycode);
  //       context->keyboardContext.removeHeldKey(mappedKey.keycode);
  //       break;

  //     default:
  //       break;
  //     }

  //     groupedEventToCycle(mappedKey);
  //     groupedEventToCycle(Key{Keycode::ALL_KEYBOARD_KEYS, mappedKey.action});
  //     groupedEventToCycle(Key{Keycode::ALL_EVENTS, mappedKey.action});
  //   });

  //   glfwSetCursorPosCallback(window,
  //     [](GLFWwindow*, double x, double y) {
  //       context->mouseContext.moveCursor(x, y);

  //       groupedEventToCycle(Key{Keycode::MOUSE_MOVE, KeyAction::UNKNOWN});
  //       groupedEventToCycle(Key{Keycode::ALL_MOUSE_EVENTS,
  //       KeyAction::UNKNOWN}); groupedEventToCycle(Key{Keycode::ALL_EVENTS,
  //       KeyAction::UNKNOWN});
  //     });

  //   glfwSetMouseButtonCallback(window,
  //     [](GLFWwindow*, int button, int action, int mods) {
  //       auto mappedButton = mapSDLMouseCodeToKey(button, action);

  //       switch (mappedButton.action) {
  //       case KeyAction::Pressed:
  //         context->mouseContext.addPressedButton(mappedButton.keycode);
  //         context->mouseContext.removeHeldButton(mappedButton.keycode);
  //         context->mouseContext.removeReleasedButton(mappedButton.keycode);
  //         break;

  //       case KeyAction::Held:
  //         context->mouseContext.addHeldButton(mappedButton.keycode);
  //         context->mouseContext.removePressedButton(mappedButton.keycode);
  //         context->mouseContext.removeReleasedButton(mappedButton.keycode);
  //         break;

  //       case KeyAction::Released:
  //         context->mouseContext.addReleasedButton(mappedButton.keycode);
  //         context->mouseContext.removePressedButton(mappedButton.keycode);
  //         context->mouseContext.removeHeldButton(mappedButton.keycode);
  //         break;

  //       default:
  //         break;
  //       }

  //       groupedEventToCycle(mappedButton);
  //       groupedEventToCycle(Key{Keycode::ALL_MOUSE_KEYS,
  //       mappedButton.action});
  //       groupedEventToCycle(Key{Keycode::ALL_MOUSE_EVENTS,
  //       mappedButton.action}); groupedEventToCycle(Key{Keycode::ALL_EVENTS,
  //       mappedButton.action});
  //     });

  //   glfwSetScrollCallback(window,
  //     [](GLFWwindow*, double x, double y) {
  //       if (y > 0) {
  //         groupedEventToCycle(Key{Keycode::MOUSE_SCROLL_DOWN,
  //         KeyAction::UNKNOWN});
  //       }

  //       if (y < 0) {
  //         groupedEventToCycle(Key{Keycode::MOUSE_SCROLL_UP,
  //         KeyAction::UNKNOWN});
  //       }

  //       context->mouseContext.moveScroll(x, y);

  //       groupedEventToCycle(Key{Keycode::MOUSE_SCROLL, KeyAction::UNKNOWN});

  //       groupedEventToCycle(Key{Keycode::ALL_MOUSE_EVENTS,
  //       KeyAction::UNKNOWN}); groupedEventToCycle(Key{Keycode::ALL_EVENTS,
  //       KeyAction::UNKNOWN});

  //       context->mouseContext.moveScroll(0, 0);
  //     });

  //   glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int
  //   codepoint) {
  //     context->keyboardContext.setCodepoint(codepoint);
  //     groupedEventToCycle(Key{Keycode::ALL_KEYBOARD_CHARS,
  //     KeyAction::UNKNOWN}); context->keyboardContext.removeCodepoint();
  //   });
  // }

  //

  void InputSystem::createTriggersFromFile(fs::path path) {
    auto triggersData =
      AssetManager::getAsset<unsigned char>(path.string().c_str());
    if (!triggersData) {
      spdlog::error("Failed to open the file {}", path.string());
      return;
    }

    YAML::Node config =
      YAML::Load(reinterpret_cast<const char*>(triggersData.get()));

    if (!config["triggers"] || !config["triggers"].IsSequence()) {
      spdlog::error(
        "Can not load actions from file {}. The 'actions' key is either "
        "missing or not a sequence.",
        path.string()
      );
      return;
    }

    for (const auto& triggerNode : config["triggers"]) {
      std::string name = triggerNode["name"].as<std::string>();
      Keys bindings;

      for (const auto& bindingNode : triggerNode["bindings"]) {
        auto key = mapStringToKeycode(bindingNode["key"].as<std::string>());
        auto actionType =
          mapStringToKeyAction(bindingNode["action"].as<std::string>());

        bindings.insert(Key{key, actionType});
      }

      addTrigger(name, bindings);

      spdlog::debug("Loaded action {}", name);
    }
  }

  //

  void InputSystem::addTrigger(
    std::string groupName,
    Keys bindings,
    Callbacks callbacks
  ) {
    forEach(callbacks, [](auto callback) {
      verify(InputSystemError, callback);
    });
    forEach(bindings, [](auto binding) {
      verify(InputSystemError, binding != Key{});
    });

    addGroupedTrigger(groupName, bindings, callbacks);
    addKeycodeTrigger(bindings, callbacks);
  }

  void InputSystem::addTrigger(
    std::string groupName,
    Keys bindings,
    Callback* callback
  ) {
    verify(InputSystemError, callback);
    forEach(bindings, [](auto binding) {
      verify(InputSystemError, binding != Key{});
    });

    addGroupedTrigger(groupName, bindings, callback);
    addKeycodeTrigger(bindings, callback);
  }

  void InputSystem::addTrigger(
    std::string groupName,
    Key binding,
    Callbacks callbacks
  ) {
    verify(InputSystemError, binding != Key{});
    forEach(callbacks, [](auto callback) {
      verify(InputSystemError, callback);
    });
    addGroupedTrigger(groupName, binding, callbacks);
    addKeycodeTrigger(binding, callbacks);
  }

  void InputSystem::addTrigger(
    std::string groupName,
    Key binding,
    Callback* callback
  ) {
    verify(InputSystemError, binding != Key{} && callback);
    addGroupedTrigger(groupName, binding, callback);
    addKeycodeTrigger(binding, callback);
  }

  void InputSystem::addTrigger(std::string groupName, Key binding) {
    verify(InputSystemError, binding != Key{});
    addGroupedTrigger(groupName, binding);
    addKeycodeTrigger(binding);
  }

  void InputSystem::addTrigger(std::string groupName, Keys bindings) {
    forEach(bindings, [](auto binding) {
      verify(InputSystemError, binding != Key{});
    });
    addGroupedTrigger(groupName, bindings);
    addKeycodeTrigger(bindings);
  }

  void InputSystem::addTrigger(std::string groupName) {
    addGroupedTrigger(groupName);
  }

  //

  void InputSystem::addTriggerBindings(std::string groupName, Keys bindings) {
    addGroupedTriggerBindings(groupName, bindings);
    addKeycodeTriggerBindings(groupName, bindings);
  }

  void InputSystem::addTriggerBindings(std::string groupName, Key binding) {
    addGroupedTriggerBindings(groupName, binding);
    addKeycodeTriggerBindings(groupName, binding);
  }

  //

  void
  InputSystem::addTriggerCallbacks(std::string groupName, Callbacks callbacks) {
    addGroupedTriggerCallbacks(groupName, callbacks);
    addKeycodeTriggerCallbacks(groupName, callbacks);
  }

  void
  InputSystem::addTriggerCallbacks(std::string groupName, Callback* callback) {
    addGroupedTriggerCallbacks(groupName, callback);
    addKeycodeTriggerCallbacks(groupName, callback);
  }

  //
  // , bool forced
  void InputSystem::removeTrigger(std::string groupName) {
    if (groupedTriggers.contains(groupName))
      return;
    std::for_each(
      groupedTriggers[groupName]->bindings.begin(),
      groupedTriggers[groupName]->bindings.end(),
      [&groupName](auto binding) {
        removeKeycodeTrigger(binding, groupedTriggers[groupName]->callbacks);
      }
    );

    groupedTriggers.erase(groupName);
  };
  // , bool forced
  void InputSystem::removeTrigger(std::set<std::string> groupNames) {
    std::for_each(groupNames.begin(), groupNames.end(), [](auto groupName) {
      removeTrigger(groupName);
    });
  };

} // namespace wind
