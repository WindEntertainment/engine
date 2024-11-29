#include "wind/dom/shadow-dom/components/root.hpp"

namespace wind::dom::shadow {
  Root::Root() : id(++nextId) { attributes.position = {0, 0}; };
  Root::Root(unsigned int id) : id(id) { attributes.position = {0, 0}; };
} // namespace wind::dom::shadow
