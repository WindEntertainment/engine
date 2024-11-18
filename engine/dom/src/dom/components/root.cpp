#include "wind/dom/dom/components/root.hpp"

namespace wind::dom {
  Root::Root(unsigned int id, const attributes::Root& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Root>(attributes)) {
          // this->root = weak_from_this();
        };
  void Root::render(wind::CommandBuffer& renderer) {};

  void Root::update() {};
} // namespace wind::dom
