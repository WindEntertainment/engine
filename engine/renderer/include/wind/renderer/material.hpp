#pragma once
#include "wind/renderer/shader.hpp"
#include "wind/renderer/texture.hpp"

namespace wind {

  struct Material {
  public:
    Material(Shader* shader, int textureCount);

    void apply();

    void setMat4(const std::string& name, const glm::mat4& transform);

    void setTexture(Texture* texture, int ind = 0);

  private:
    std::vector<Texture*> textures;
    Shader* shader;
  };

} // namespace wind