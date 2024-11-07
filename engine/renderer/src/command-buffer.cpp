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

  CommandBuffer::CommandBuffer(std::shared_ptr<RenderContext> context)
      : context(context) {};

} // namespace wind
