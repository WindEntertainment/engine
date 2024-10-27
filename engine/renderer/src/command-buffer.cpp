#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/command-buffer.hpp"

namespace wind {

  void CommandBuffer::submit() {
    if (!context->getCamera())
      return;

    for (const auto& command : commands)
      command();
  }

  void CommandBuffer::clear(glm::vec4 color) {
    commands.emplace_back([=]() {
      glClearColor(color.r, color.g, color.b, color.a);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    });
  }

  void CommandBuffer::drawMesh(
    Mesh* mesh,
    glm::mat4x4& transform,
    Material* material
  ) {
    commands.emplace_back([=]() {
      glBindVertexArray(mesh->id());
      material->setMat4("model", transform);
      material->setMat4("view", context->getCamera()->getTransform());
      material->setMat4("projection", context->getCamera()->getProjection());
      material->apply();
      glDrawElements(GL_TRIANGLES, mesh->length(), GL_UNSIGNED_INT, 0);
    });
  }

  CommandBuffer::CommandBuffer(std::shared_ptr<RenderContext> context)
      : context(context) {};

} // namespace wind