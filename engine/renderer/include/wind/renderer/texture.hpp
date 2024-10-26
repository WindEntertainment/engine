#pragma once
#include "wind/utils/utils.hpp"

namespace wind {
  class Texture {
  public:
    Texture(const unsigned char* pixels, const glm::ivec2 size);
    ~Texture();

    uint id() const;

  private:
    uint texture_id = 0;
  };

} // namespace wind
