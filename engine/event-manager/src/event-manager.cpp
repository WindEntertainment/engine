#include "wind/event-manager/event-manager.hpp"

namespace wind {

  int EventManager::nextCallbackId = 0;
  EventManager::Callbacks EventManager::events = {};

} // namespace wind
