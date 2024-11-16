#include "wind/dom/dom/components/text.hpp"

namespace wind::dom {
  Text::Text(unsigned int id, attributes::Text attributes)
      : UIElement(id), attributes(std::move(attributes)) {};

  void Text::render(wind::CommandBuffer& renderer) { std::cout << "I'm Text"; };

  void Text::reset() { attributes = attributes::defaultTextAttributes; };

  void Text::update() {};
} // namespace wind::dom
