#pragma once
#include "wind/renderer/material.hpp"
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/render_context.hpp"
#include "wind/renderer/camera.hpp"

namespace wind {

  using RenderCommand = std::function<void(void)>;

  class CommandBuffer {
  public:
    CommandBuffer(std::shared_ptr<RenderContext> context);

    void submit();

    void clear(glm::vec4 color);
    void drawMesh(Mesh* mesh, glm::mat4x4& transform, Material* material);
    void setCurrentCamera(Camera* camera);

  private:
    std::vector<RenderCommand> commands;
    std::shared_ptr<RenderContext> context;
  };

} // namespace wind