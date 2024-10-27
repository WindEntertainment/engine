#pragma once
#include "wind/utils/utils.hpp"

namespace wind {
  class Camera {
  public:
    Camera(
      glm::vec3 position,
      glm::vec3 front,
      glm::vec3 up,
      glm::ivec2 viewSize
    );

    void setPosition(glm::vec3 position);
    void setFront(glm::vec3 front);
    void setUp(glm::vec3 up);

    void setOrtho(glm::ivec2 viewSize);
    glm::ivec2 viewSize();

    glm::mat4 getTransform();
    glm::mat4 getProjection();

  private:
    glm::ivec2 projectionViewSize;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    glm::mat4 transform;
    glm::mat4 projection;
  };
} // namespace wind