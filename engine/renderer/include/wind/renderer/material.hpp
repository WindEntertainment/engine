#pragma once
#include "wind/renderer/shader.hpp"
#include "wind/renderer/texture.hpp"

namespace wind {

  struct Material {
  public:
    Material(std::shared_ptr<Shader> shader, int textureCount);

    void apply();

    void setMat4(const std::string& name, const glm::mat4& transform);
    void setVec4(const std::string& name, const glm::vec4& vec);

    void setTexture(std::shared_ptr<Texture> texture, int ind = 0);

  private:
    std::vector<std::shared_ptr<Texture>> textures;
    std::shared_ptr<Shader> shader;
  };

} // namespace wind