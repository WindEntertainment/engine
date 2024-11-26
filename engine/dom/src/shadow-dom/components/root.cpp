#include "wind/dom/shadow-dom/components/root.hpp"

namespace wind::dom::shadow {
  Root::Root() : id(++nextId) {};
  Root::Root(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
