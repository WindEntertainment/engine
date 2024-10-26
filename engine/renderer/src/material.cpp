#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/material.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace wind {

Material::Material(Shader* shader)
    : shader(shader) {};

void Material::apply() {
  glUseProgram(shader->id());
  for (auto setter : setters)
    setter();
}

void Material::setMat4(const std::string& name, const glm::mat4& transform) {
  setters.emplace_back([=]() {
    int loc = glGetUniformLocation(shader->id(), name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform));
  });
}

} // namespace wind