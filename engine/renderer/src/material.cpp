#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/material.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace wind {

  Material::Material(Shader* shader, int textureCount) : shader(shader) {
    textures.resize(textureCount);
    std::fill(textures.begin(), textures.end(), nullptr);
  };

  void Material::apply() {
    glUseProgram(shader->id());

    for (int i = 0; i < textures.size(); ++i) {
      if (textures[i] == nullptr)
        continue;

      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]->id());
    }
  }

  void Material::setMat4(const std::string& name, const glm::mat4& transform) {
    int loc = glGetUniformLocation(shader->id(), name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform));
  }

  void Material::setTexture(Texture* texture, int ind) {
    if (textures.size() < ind) {
      spdlog::error(
        "Texture index {} is out of bounds. Valid indices are 0 to {}.",
        ind,
        textures.size() - 1
      );
      return;
    }

    textures[ind] = texture;
  }

} // namespace wind