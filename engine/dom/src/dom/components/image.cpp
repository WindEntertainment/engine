#include "wind/dom/dom/components/image.hpp"

namespace wind::dom {
  Image::Image(unsigned int id, const attributes::Image& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Image>(attributes)) {};
  void Image::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm Image";
  };

  void Image::update() {};

} // namespace wind::dom
