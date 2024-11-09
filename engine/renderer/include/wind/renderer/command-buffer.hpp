#pragma once
#include "wind/renderer/material.hpp"
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/sprite.hpp"
#include "wind/renderer/render_context.hpp"
#include "wind/renderer/camera.hpp"
#include "wind/renderer/procedural-graphics.hpp"
#include "wind/renderer/text-mesh.hpp"

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

    void drawCircle(
      std::shared_ptr<CircleMesh> mesh,
      glm::vec2 position,
      float radius,
      glm::vec4 color,
      const std::shared_ptr<Texture>& texture
    );

    void drawText(
      std::shared_ptr<Font> font,
      std::string text,
      glm::vec2 position, 
      glm::vec2 scale, 
      glm::vec4 color, 
      int letterSpacing = 0,
      int lineWidth = 0,
      int lineSpacing = 12
    );

    void drawText(
      std::shared_ptr<TextMesh> mesh,
      glm::vec2 position,
      glm::vec2 scale,
      glm::vec4 color
    );

    void setCurrentCamera(Camera* camera);

  private:
    std::vector<RenderCommand> commands;
    std::shared_ptr<RenderContext> context;
  };

} // namespace wind
