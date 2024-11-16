#include "wind/dom/dom/components/root.hpp"

namespace wind::dom {
  Root::Root(unsigned int id, attributes::Root attributes)
      : UIElement(id), attributes(std::move(attributes)) {
          // this->root = weak_from_this();
        };
  void Root::render(wind::CommandBuffer& renderer) {};

  void Root::reset() { attributes = attributes::defaultRootAttributes; }

  void Root::update() {};
} // namespace wind::dom
