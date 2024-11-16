#include "wind/dom/dom/components/image.hpp"

namespace wind::dom {
  Image::Image(unsigned int id, attributes::Image attributes)
      : UIElement(id), attributes(std::move(attributes)) {};
  void Image::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm Image";
  };

  void Image::reset() { attributes = attributes::defaultImageAttributes; };

  void Image::update() {};

} // namespace wind::dom
