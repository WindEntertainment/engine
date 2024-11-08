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

  std::shared_ptr<InputSystemContext> InputSystem::context =
    wind::share(InputSystemContext());

  std::unordered_map<Key, Callbacks, KeyHash> InputSystem::keycodeTriggers;
  std::map<std::string, std::shared_ptr<Trigger>> InputSystem::groupedTriggers;
  int nextCallbackId = 0;

  inline void InputSystem::groupedEventToCycle(Key keycode) {
    if (keycodeTriggers.contains(keycode)) {
      std::ranges::for_each(keycodeTriggers[keycode], [](Callback* callback) {
        (*callback)(context);
      });
    }
  }

  void InputSystem::handleKeyPress(
    SDL_Keycode key,
    int scancode,
    int action,
    int mods
  ) {
    Key mappedKey = mapSDLKeycodeToKey(key, action);
    context->key = mappedKey;
    switch (mappedKey.action) {
      case KeyAction::Pressed:
        context->keyboardContext.addPressedKey(mappedKey.keycode);
        context->keyboardContext.removeHeldKey(mappedKey.keycode);
        context->keyboardContext.removeReleasedKey(mappedKey.keycode);
        break;

      case KeyAction::Held:
        context->keyboardContext.addHeldKey(mappedKey.keycode);
        context->keyboardContext.removePressedKey(mappedKey.keycode);
        context->keyboardContext.removeReleasedKey(mappedKey.keycode);
        break;

      case KeyAction::Released:
        context->keyboardContext.addReleasedKey(mappedKey.keycode);
        context->keyboardContext.removePressedKey(mappedKey.keycode);
        context->keyboardContext.removeHeldKey(mappedKey.keycode);
        break;

      default: break;
    }

    groupedEventToCycle(mappedKey);
    groupedEventToCycle(
      Key{.keycode = Keycode::K_AllKeys, .action = mappedKey.action}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::AllEvents, .action = mappedKey.action}
    );
  }

  void InputSystem::handleMousePress(uint button, int action, int mods) {
    Key mappedButton = mapSDLMouseCodeToKey(button, action);
    context->key = mappedButton;
    switch (mappedButton.action) {
      case KeyAction::Pressed:
        context->mouseContext.addPressedButton(mappedButton.keycode);
        context->mouseContext.removeHeldButton(mappedButton.keycode);
        context->mouseContext.removeReleasedButton(mappedButton.keycode);
        break;

      case KeyAction::Held:
        context->mouseContext.addHeldButton(mappedButton.keycode);
        context->mouseContext.removePressedButton(mappedButton.keycode);
        context->mouseContext.removeReleasedButton(mappedButton.keycode);
        break;

      case KeyAction::Released:
        context->mouseContext.addReleasedButton(mappedButton.keycode);
        context->mouseContext.removePressedButton(mappedButton.keycode);
        context->mouseContext.removeHeldButton(mappedButton.keycode);
        break;

      default: break;
    }

    groupedEventToCycle(mappedButton);
    groupedEventToCycle(
      Key{.keycode = Keycode::M_AllKeys, .action = mappedButton.action}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::M_AllEvents, .action = mappedButton.action}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::AllEvents, .action = mappedButton.action}
    );
  }

  void InputSystem::handleMouseMove(double x, double y) {
    context->mouseContext.moveCursor(x, y);
    context->key =
      Key{.keycode = Keycode::M_Move, .action = KeyAction::Unknown};
    groupedEventToCycle(
      Key{.keycode = Keycode::M_Move, .action = KeyAction::Unknown}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::M_AllEvents, .action = KeyAction::Unknown}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::AllEvents, .action = KeyAction::Unknown}
    );
  }

  void InputSystem::handleScroll(double x, double y) {
    context->key =
      Key{.keycode = Keycode::M_Scroll, .action = KeyAction::Unknown};
    if (y > 0) {
      groupedEventToCycle(
        Key{.keycode = Keycode::M_ScrollDown, .action = KeyAction::Unknown}
      );
    }

    if (y < 0) {
      groupedEventToCycle(
        Key{.keycode = Keycode::M_ScrollUp, .action = KeyAction::Unknown}
      );
    }

    context->mouseContext.moveScroll(x, y);

    groupedEventToCycle(
      Key{.keycode = Keycode::M_Scroll, .action = KeyAction::Unknown}
    );

    groupedEventToCycle(
      Key{.keycode = Keycode::M_AllEvents, .action = KeyAction::Unknown}
    );
    groupedEventToCycle(
      Key{.keycode = Keycode::AllEvents, .action = KeyAction::Unknown}
    );

    context->mouseContext.moveScroll(0, 0);
  }

  void InputSystem::handleCharPress(uint codepoint) {
    context->keyboardContext.setCodepoint(codepoint);
    context->key = Key{Keycode::K_AllChars, .action = KeyAction::Unknown};
    groupedEventToCycle(
      Key{.keycode = Keycode::K_AllChars, .action = KeyAction::Unknown}
    );
    context->keyboardContext.removeCodepoint();
  }

  void InputSystem::handleEvent(SDL_Event& event) {
    switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        handleKeyPress(
          event.key.keysym.sym,
          event.key.keysym.scancode,
          event.type,
          event.key.keysym.mod
        );
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        handleMousePress(event.button.button, event.type, event.button.clicks);
        break;

      case SDL_MOUSEMOTION:
        handleMouseMove(
          static_cast<double>(event.motion.x),
          static_cast<double>(event.motion.y)
        );
        break;

      case SDL_TEXTINPUT:
        handleCharPress(static_cast<uint>(event.text.text[0]));
        break;

      case SDL_MOUSEWHEEL:
        handleScroll(
          static_cast<double>(event.wheel.x), static_cast<double>(event.wheel.y)
        );
        break;
      default: break;
    }
  }

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
      auto name = triggerNode["name"].as<std::string>();
      Keys bindings;

      for (const auto& bindingNode : triggerNode["bindings"]) {
        auto key = mapStringToKeycode(bindingNode["key"].as<std::string>());
        auto actionType =
          mapStringToKeyAction(bindingNode["action"].as<std::string>());

        bindings.insert(Key{.keycode = key, .action = actionType});
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
    std::ranges::for_each(groupNames, [](auto groupName) {
      removeTrigger(groupName);
    });
  };

} // namespace wind
