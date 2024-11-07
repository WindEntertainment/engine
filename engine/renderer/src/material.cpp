#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/material.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace wind {

  Material::Material(std::shared_ptr<Shader> shader, int textureCount)
      : shader(shader) {
    textures.resize(textureCount);
    std::fill(textures.begin(), textures.end(), nullptr);
  };

  void Material::apply() {
    glUseProgram(shader->id());

    for (int i = 0; i < textures.size(); ++i) {
      glActiveTexture(GL_TEXTURE0 + i);

      if (textures[i] == nullptr) {
        spdlog::info("texture is nullptr");
        glBindTexture(GL_TEXTURE_2D, 0);
      } else
        glBindTexture(GL_TEXTURE_2D, textures[i]->id());
    }
  }

  void Material::setMat4(const std::string& name, const glm::mat4& transform) {
    int loc = glGetUniformLocation(shader->id(), name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform));
  }

  void Material::setVec4(const std::string& name, const glm::vec4& vec) {
    int loc = glGetUniformLocation(shader->id(), name.c_str());
    glUniform4fv(loc, 1, glm::value_ptr(vec));
  }

  void Material::setTexture(std::shared_ptr<Texture> texture, int ind) {
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
