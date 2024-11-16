#include "wind/dom/dom/components/checkbox.hpp"

namespace wind::dom {
  Checkbox::Checkbox(unsigned int id, attributes::Checkbox attributes)
      : UIElement(id), attributes(std::move(attributes)) {};
  void Checkbox::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Checkbox::reset() {
    attributes = attributes::defaultCheckboxAttributes;
  };

  void Checkbox::update() {};
} // namespace wind::dom
