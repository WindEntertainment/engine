#include "wind/dom/dom/components/checkbox.hpp"

namespace wind::dom {
  Checkbox::Checkbox(unsigned int id, const attributes::Checkbox& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Checkbox>(attributes)) {};
  void Checkbox::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Checkbox::update() {};
} // namespace wind::dom
