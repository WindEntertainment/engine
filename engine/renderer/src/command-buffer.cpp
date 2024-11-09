#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/command-buffer.hpp"
#include "wind/asset-pipeline/asset-manager.hpp"
#include "wind/renderer/assets.hpp"

#include <glm/ext/matrix_transform.hpp>

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
    const std::shared_ptr<Mesh>& mesh,
    glm::mat4x4& transform,
    const std::shared_ptr<Material>& material
  ) {
    commands.emplace_back([=]() {
      glBindVertexArray(mesh->id());

      material->apply();
      material->setMat4("uModel", transform);
      material->setMat4("uView", context->getCamera()->getTransform());
      material->setMat4("uProjection", context->getCamera()->getProjection());

      glDrawElements(GL_TRIANGLES, mesh->length(), GL_UNSIGNED_INT, 0);
    });
  }

  void CommandBuffer::drawRect(
    glm::vec2 position,
    glm::vec2 size,
    glm::vec4 color,
    const std::shared_ptr<Texture>& texture,
    float angle,
    float borderRadius
  ) {
    static std::shared_ptr<Mesh> mesh =
      AssetManager::getAsset<Mesh>("default-rect-mesh");
    static std::shared_ptr<Material> material =
      AssetManager::getAsset<Material>("default-ui-material");
    static std::shared_ptr<Texture> defaultTexture =
      AssetManager::getAsset<Texture>("default-white-texture");

    commands.emplace_back([=]() {
      glBindVertexArray(mesh->id());

      glm::mat4 transform = glm::mat4(1);
      transform = glm::translate(transform, {position, 0});
      transform = glm::rotate(transform, angle, {0.0f, 0.0f, 1.0f});
      transform = glm::scale(transform, {size, 1});

      material->setTexture(texture == nullptr ? defaultTexture : texture, 0);
      material->apply();
      material->setVec4("uColor", color);
      material->setMat4("uModel", transform);
      material->setMat4("uProjection", context->getCamera()->getProjection());

      glDrawElements(GL_TRIANGLES, mesh->length(), GL_UNSIGNED_INT, 0);
    });
  }

  void CommandBuffer::drawCircle(
    std::shared_ptr<CircleMesh> mesh,
    glm::vec2 position,
    float radius,
    glm::vec4 color,
    const std::shared_ptr<Texture>& texture
  ) {
    static std::shared_ptr<Material> material =
      AssetManager::getAsset<Material>("default-ui-material");
    static std::shared_ptr<Texture> defaultTexture =
      AssetManager::getAsset<Texture>("default-white-texture");

    commands.emplace_back([=]() {
      glBindVertexArray(mesh->id());

      glm::mat4 transform = glm::mat4(1);
      transform = glm::translate(transform, {position, 0});
      transform = glm::scale(transform, {radius, radius, 1});

      material->setTexture(texture == nullptr ? defaultTexture : texture, 0);
      material->apply();
      material->setVec4("uColor", color);
      material->setMat4("uModel", transform);
      material->setMat4("uProjection", context->getCamera()->getProjection());

      glDrawElements(GL_TRIANGLES, mesh->length(), GL_UNSIGNED_INT, 0);
    });
  }

  void CommandBuffer::drawSprite(
    const std::shared_ptr<Sprite>& sprite,
    glm::mat4x4& transform
  ) {
    commands.emplace_back([=]() {
      glBindVertexArray(sprite->id());

      auto material = sprite->getMaterial();

      material->apply();
      material->setMat4("uModel", transform);
      material->setMat4("uView", context->getCamera()->getTransform());
      material->setMat4("uProjection", context->getCamera()->getProjection());

      glDrawElements(GL_TRIANGLES, sprite->length(), GL_UNSIGNED_INT, 0);
    });
  }

  void CommandBuffer::drawText(
    std::shared_ptr<TextMesh> mesh,
    glm::vec2 position,
    glm::vec2 scale,
    glm::vec4 color
  ) {
    static std::shared_ptr<Mesh> rectMesh =
      AssetManager::getAsset<Mesh>("default-rect-mesh");
    static std::shared_ptr<Material> material =
      AssetManager::getAsset<Material>("default-text-material");

    commands.emplace_back([=]() { 
      glBindVertexArray(rectMesh->id());

      glm::vec2 offset = {};

      for (int i = 0; i < mesh->glyphs.size(); ++i) {
        auto glyph = mesh->glyphs[i];

        glm::mat4 transform = glm::mat4(1);
        
        transform = glm::translate(transform, {
          position.x + offset.x + glyph.size.x / 2 * scale.x + glyph.bearing.x * scale.x,
          position.y + offset.y + glyph.size.y / 2 * scale.y - (glyph.size.y - glyph.bearing.y) * scale.y,
          0
        });

        transform = glm::scale(transform, {
          glyph.size.x * scale.x,
          glyph.size.y * scale.y,
          1
         });

        offset.x += ((glyph.advance.x >> 6) + mesh->letterSpacing) * scale.x;
        if ((mesh->lineWidth != 0 && offset.x > mesh->lineWidth * scale.x) || glyph.character == '\n') {
          offset.x = 0;
          offset.y -= ((glyph.advance.y >> 6) + mesh->lineSpacing) * scale.y;
        }

        if (glyph.character == '\n')
          continue;

        material->setTexture(glyph.texture);
        material->apply();
        material->setVec4("uColor", color);
        material->setMat4("uModel", transform);
        material->setMat4("uProjection", context->getCamera()->getProjection());

        glDrawElements(GL_TRIANGLES, rectMesh->length(), GL_UNSIGNED_INT, 0);
      }
    });
  }

  CommandBuffer::CommandBuffer(std::shared_ptr<RenderContext> context)
      : context(context) {};

} // namespace wind
