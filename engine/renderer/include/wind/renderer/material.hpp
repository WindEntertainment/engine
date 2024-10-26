#pragma once
#include "wind/renderer/shader.hpp"

namespace wind {

struct Material {
public:
  Material(Shader* shader);

  void apply();

  void setMat4(const std::string& name, const glm::mat4& transform);

private:
  std::vector<std::function<void()>> setters;
  Shader* shader;
};

} // namespace wind