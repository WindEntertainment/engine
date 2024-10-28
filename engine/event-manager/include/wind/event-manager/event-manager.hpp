#pragma once
#include "wind/utils/utils.hpp"

namespace wind {
  class Event {
  public:
    virtual ~Event() = default;
  };
  class EventManager {
  public:
    using Callback = std::function<void(std::shared_ptr<Event>)>;
    using Callbacks =
      std::unordered_map<std::string, std::vector<std::pair<int, Callback>>>;

    static Callbacks events;
    static int nextCallbackId;

    template <typename T>
      requires std::derived_from<T, Event>
    static int on(std::function<void(std::shared_ptr<T>)> callback) {
      const std::string typeName = typeid(T).name();
      int callbackId = nextCallbackId++;

      events[typeName].emplace_back(
        callbackId,
        [callback](std::shared_ptr<Event> eventPtr) {
          callback(std::dynamic_pointer_cast<T>(eventPtr));
        }
      );

      return callbackId;
    }

    template <typename T>
      requires std::derived_from<T, Event>
    static void fire(T event) {
      auto eventPtr = std::make_shared<T>(std::move(event));
      const std::string typeName = typeid(T).name();

      auto it = events.find(typeName);
      if (it != events.end()) {
        for (const auto& [id, callback] : it->second) {
          callback(eventPtr);
        }
      }
    }

    template <typename T>
      requires std::derived_from<T, Event>
    static void off(int callbackId) {
      const std::string typeName = typeid(T).name();
      auto it = events.find(typeName);
      if (it != events.end()) {
        auto& callbacks = it->second;
        callbacks.erase(
          std::remove_if(
            callbacks.begin(),
            callbacks.end(),
            [callbackId](const std::pair<int, Callback>& pair) {
              return pair.first == callbackId;
            }
          ),
          callbacks.end()
        );
      }
    }

    template <typename T>
      requires std::derived_from<T, Event>
    static void offEvent() {
      const std::string typeName = typeid(T).name();
      events.erase(typeName);
    }
  };
} // namespace wind
