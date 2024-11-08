#pragma once
#include <wind/utils/includes.hpp>

#include "wind/input-system/context.hpp"
#include "wind/input-system/trigger.hpp"
#include "wind/input-system/keys.hpp"
#include "wind/window/window.hpp"

namespace wind {

  class InputSystem {
  public:
    // static void init(GLFWwindow* window);

    static void
    handleKeyPress(SDL_Keycode key, int scancode, int action, int mods);
    static void handleMousePress(uint button, int action, int mods);
    static void handleMouseMove(double x, double y);
    static void handleCharPress(uint codepoint);
    static void handleScroll(double x, double y);

    static void handleEvent(SDL_Event& event);

    static void createTriggersFromFile(std::filesystem::path path);

    static void
    addTrigger(std::string groupName, Keys bindings, Callbacks callbacks);
    static void
    addTrigger(std::string groupName, Keys bindings, Callback* callback);
    static void
    addTrigger(std::string groupName, Key binding, Callbacks callbacks);
    static void
    addTrigger(std::string groupName, Key binding, Callback* callback);
    static void addTrigger(std::string groupName, Key binding);
    static void addTrigger(std::string groupName, Keys bindings);
    static void addTrigger(std::string groupName);

    static void addTriggerBindings(std::string groupName, Keys bindings);
    static void addTriggerBindings(std::string groupName, Key binding);

    static void addTriggerCallbacks(std::string groupName, Callbacks callbacks);
    static void addTriggerCallbacks(std::string groupName, Callback* callback);

    static void removeTriggerBindings(std::string groupName, Keys bindings);
    static void removeTriggerBindings(std::string groupName, Key binding);

    static void
    removeTriggerCallbacks(std::string groupName, Callbacks callbacks);
    static void
    removeTriggerCallbacks(std::string groupName, Callback* callback);

    static void removeTrigger(std::string groupName);
    static void removeTrigger(std::set<std::string> groupNames);

    static std::unordered_map<Key, Callbacks, KeyHash> keycodeTriggers;
    static std::map<std::string, std::shared_ptr<Trigger>> groupedTriggers;

    static std::shared_ptr<InputSystemContext> context;

  private:
    static inline void groupedEventToCycle(Key keycode);

    static void addKeycodeTrigger(Keys bindings, Callbacks callbacks);
    static void addKeycodeTrigger(Keys bindings, Callback* callback);
    static void addKeycodeTrigger(Key binding, Callbacks callbacks);
    static void addKeycodeTrigger(Key binding, Callback* callback);
    static void addKeycodeTrigger(Keys bindings);
    static void addKeycodeTrigger(Key binding);

    static void addKeycodeTriggerBindings(std::string groupName, Key binding);
    static void addKeycodeTriggerBindings(std::string groupName, Keys bindings);

    static void
    addKeycodeTriggerCallbacks(std::string groupName, Callback* callback);
    static void
    addKeycodeTriggerCallbacks(std::string groupName, Callbacks callbacks);

    static void
    addGroupedTrigger(std::string groupName, Keys bindings, Callbacks callbacks);
    static void
    addGroupedTrigger(std::string groupName, Keys bindings, Callback* callback);
    static void
    addGroupedTrigger(std::string groupName, Key binding, Callbacks callbacks);
    static void
    addGroupedTrigger(std::string groupName, Key binding, Callback* callback);
    static void addGroupedTrigger(std::string groupName, Keys bindings);
    static void addGroupedTrigger(std::string groupName, Key binding);
    static void addGroupedTrigger(std::string groupName);

    static void addGroupedTriggerBindings(std::string groupName, Key binding);
    static void addGroupedTriggerBindings(std::string groupName, Keys bindings);

    static void
    addGroupedTriggerCallbacks(std::string groupName, Callback* callback);
    static void
    addGroupedTriggerCallbacks(std::string groupName, Callbacks callbacks);

    static void removeKeycodeTrigger(Key binding, Callbacks callbacks);
    static void removeKeycodeTrigger(Callbacks callbacks);
    static void removeKeycodeTrigger(Key binding, Callback* callback);
    static void removeKeycodeTrigger(Callback* callback);
  };
} // namespace wind
