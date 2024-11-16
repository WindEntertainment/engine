#include "wind/dom/dom/components/select.hpp"

namespace wind::dom {
  Select::Select(unsigned int id, attributes::Select attributes)
      : UIElement(id), attributes(std::move(attributes)) {};
  void Select::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Select::reset() { attributes = attributes::defaultSelectAttributes; };

  void Select::update() {};
} // namespace wind::dom
