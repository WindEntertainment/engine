#pragma once
#include "wind/renderer/material.hpp"
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/render_context.hpp"

namespace wind {

using RenderCommand = std::function<void(void)>;

class CommandBuffer {
public:
  void submit();

  void clear(glm::vec4 color);
  void drawMesh(Mesh* mesh, glm::mat4x4& transform, Material* material);

private:
  std::vector<RenderCommand> commands = {};
};

} // namespace wind