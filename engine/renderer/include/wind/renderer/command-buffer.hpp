#pragma once
#include "wind/renderer/material.hpp"
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/sprite.hpp"
#include "wind/renderer/render_context.hpp"
#include "wind/renderer/camera.hpp"

namespace wind {

  using RenderCommand = std::function<void(void)>;

  class CommandBuffer {
  public:
    CommandBuffer(std::shared_ptr<RenderContext> context);

    void submit();

    void clear(glm::vec4 color);

    void drawMesh(
      const std::shared_ptr<Mesh>& mesh,
      glm::mat4x4& transform,
      const std::shared_ptr<Material>& material
    );

    void
    drawSprite(const std::shared_ptr<Sprite>& sprite, glm::mat4x4& transform);

    void drawRect(
      glm::vec2 position,
      glm::vec2 size,
      glm::vec4 color,
      const std::shared_ptr<Texture>& texture,
      float angle,
      float borderRadius
    );

    void setCurrentCamera(Camera* camera);

  private:
    std::vector<RenderCommand> commands;
    std::shared_ptr<RenderContext> context;
  };

} // namespace wind