#include "wind/renderer/camera.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace wind {

  Camera::Camera(
    glm::vec3 position,
    glm::vec3 front,
    glm::vec3 up,
    glm::ivec2 viewSize
  )
      : position(position), front(front), up(up) {
    setOrtho(viewSize);
  }

  void Camera::setPosition(glm::vec3 cameraPosition) {
    position = cameraPosition;
  }

  void Camera::setFront(glm::vec3 frontVector) { front = frontVector; }

  void Camera::setUp(glm::vec3 upVector) { up = upVector; }

  void Camera::setOrtho(glm::ivec2 viewSize) {
    projectionViewSize = viewSize;
    projection = glm::ortho(
      -static_cast<float>(viewSize.x) / 2.f,
      static_cast<float>(viewSize.x) / 2.f,
      -static_cast<float>(viewSize.y) / 2.f,
      static_cast<float>(viewSize.y) / 2.f,
      -1.f,
      1.f
    );
  }

  glm::mat4 Camera::getTransform() {
    transform = glm::lookAt(position, position + front, up);
    return transform;
  }

  glm::mat4 Camera::getProjection() { return projection; }

} // namespace wind