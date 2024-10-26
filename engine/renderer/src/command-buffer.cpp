#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/command-buffer.hpp"

namespace wind {

void CommandBuffer::submit() {
  for (auto command : commands)
    command();
}

void CommandBuffer::clear(glm::vec4 color) {
  commands.emplace_back([=]() {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  });
}

void CommandBuffer::drawMesh(Mesh* mesh, glm::mat4x4& transform, Material* material) {
  commands.emplace_back([=]() {
    glBindVertexArray(mesh->id());
    material->setMat4("model", transform);
    material->apply();
    glDrawElements(GL_TRIANGLES, mesh->length(), GL_UNSIGNED_INT, 0);
  });
}

} // namespace wind