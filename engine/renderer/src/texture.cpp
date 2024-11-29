#include "wind/renderer/opengl_includes.hpp"
#include "wind/renderer/texture.hpp"

#include "wind/utils/utils.hpp"

#include <glm/ext/scalar_uint_sized.hpp>

namespace wind {

  uint Texture::id() const { return texture_id; }

  Texture::Texture(void* pixels, const glm::ivec2 size) {
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      size.x,
      size.y,
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      pixels
    );

    // glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::~Texture() { glDeleteTextures(1, &texture_id); }
} // namespace wind
