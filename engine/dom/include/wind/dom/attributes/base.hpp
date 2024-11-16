#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"

namespace wind::dom::attributes {
  struct Base {
    bool disabled = {false};
    std::function<void()> onClick = {};
    std::function<void()> onHover = {};
    std::function<void()> onDragStart = {};
    std::function<void()> onDrag = {};
    std::function<void()> onDragEnd = {};
    std::function<void()> onFocus = {};
    glm::vec2 position = {0, 0};
    glm::vec2 size = {100, 100};
    glm::vec4 backgroundColor = {0.4f, 0.4f, 0.4f, 1.f};
    std::shared_ptr<Texture> texture = {};
    float angle = {};
    float borderRadius = {};
    float borderWidth = {};
    glm::vec4 borderColor = {};

    bool isHovered = false;

    bool compareBase(const attributes::Base& attributes) {
      return std::tie(
               this->disabled,
               this->position,
               this->size,
               this->backgroundColor,
               this->texture,
               this->angle,
               this->borderRadius,
               this->borderWidth,
               this->borderColor,
               this->isHovered
             ) ==
             std::tie(
               attributes.disabled,
               attributes.position,
               attributes.size,
               attributes.backgroundColor,
               attributes.texture,
               attributes.angle,
               attributes.borderRadius,
               attributes.borderWidth,
               attributes.borderColor,
               attributes.isHovered
             );
    };

    virtual bool compare(const attributes::Base& attributes) = 0;

    bool operator==(const attributes::Base& element) {
      return compareBase(element) && compare(element);
    };
  };
} // namespace wind::dom::attributes
