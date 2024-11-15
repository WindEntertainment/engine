
// #pragma once
// #include <glm/vec2.hpp>
// #include <memory>
// #include <string>
// #include <functional>

// #include <unordered_set>
// #include <memory>

// namespace editor::spriteSheetManager {
//   enum class ResizeDirection {
//     None,
//     Top,
//     Bottom,
//     Left,
//     Right,
//     TopLeft,
//     TopRight,
//     BottomLeft,
//     BottomRight
//   };

//   template <typename T>
//   ResizeDirection
//   GetResizeDirection(std::shared_ptr<T> rect, glm::vec2 mousePos) {
//     // if (rect == nullptr) {
//     //   return ResizeDirection::None;
//     // }
//     spdlog::info(
//       "{} {} {} {}", mousePos.x, rect->topLeft.x, mousePos.y, rect->topLeft.y
//     );
//     auto padding = 8.0f;
//     bool nearLeft = mousePos.x >= rect->topLeft.x - padding &&
//                     mousePos.x <= rect->topLeft.x + padding;
//     bool nearRight = mousePos.x >= rect->bottomRight.x - padding &&
//                      mousePos.x <= rect->bottomRight.x + padding;
//     bool nearTop = mousePos.y >= rect->topLeft.y - padding &&
//                    mousePos.y <= rect->topLeft.y + padding;
//     bool nearBottom = mousePos.y >= rect->bottomRight.y - padding &&
//                       mousePos.y <= rect->bottomRight.y + padding;
//     if (nearLeft && nearTop)
//       return ResizeDirection::TopLeft;
//     if (nearRight && nearTop)
//       return ResizeDirection::TopRight;
//     if (nearLeft && nearBottom)
//       return ResizeDirection::BottomLeft;
//     if (nearRight && nearBottom)
//       return ResizeDirection::BottomRight;
//     if (nearTop)
//       return ResizeDirection::Top;
//     if (nearBottom)
//       return ResizeDirection::Bottom;
//     if (nearLeft)
//       return ResizeDirection::Left;
//     if (nearRight)
//       return ResizeDirection::Right;

//     return ResizeDirection::None;
//   };
//   // ImVec2 glmToImVec2(const glm::vec2& vec) { return ImVec2(vec.x, vec.y);
//   }
//   // glm::vec2 imToGlmVec2(const ImVec2& vec) { return glm::vec2(vec.x,
//   vec.y); }

//   template <typename T>
//   class BehaviorWrapper {
//   public:
//     std::string id;
//     std::function<void()> start;
//     std::function<void()> move;
//     std::function<void()> end;
//     std::function<void()> use;

//     BehaviorWrapper(
//       const std::string& id,
//       std::function<void()> start,
//       std::function<void()> move,
//       std::function<void()> end
//     )
//         : id(id), start(start), move(move), end(end) {
//   use = [start, move, end]() {
//     start();
//     move();
//     end();
//   };
// }
//   };

//   template <typename T>
//   concept HasSize = requires(T t) {
//     { t.topLeft } -> std::convertible_to<glm::vec2>;
//     { t.bottomRight } -> std::convertible_to<glm::vec2>;
//   };

//   // // Concept for types that have a `name` field of type `std::string`
//   // template <typename T>
//   // concept HasName = requires(T t) {
//   //   { t.name } -> std::convertible_to<std::string>;
//   // };

//   // // A combined concept that requires both `HasPosition` and `HasName`
//   // template <typename T>
//   // concept HasPositionAndName = HasPosition<T> && HasName<T>;

//   template <HasSize T>
//   class BehaviorFactory {
//   public:
//     static std::shared_ptr<BehaviorWrapper<T>>
//     createDraggable(std::shared_ptr<T> obj) {
//       return wind::share(BehaviorWrapper<T>(
//         "Draggable",
//         [obj]() mutable {
//           if (!ImGui::IsMouseClicked(0))
//             return;

//           auto io = ImGui::GetIO();
//           auto direction =
//             GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x,
//             io.MousePos.y));

//           if (direction != ResizeDirection::None)
//             return;

//           if (io.MousePos.x >= obj->topLeft.x &&
//               io.MousePos.x <= obj->bottomRight.x &&
//               io.MousePos.y >= obj->topLeft.y &&
//               io.MousePos.y <= obj->bottomRight.y) {
//             obj->isDragging = true;
//             obj->dragOffset =
//               glm::vec2(io.MousePos.x, io.MousePos.y) - obj->topLeft;
//             // imToGlmVec2(io.MousePos) - obj->topLeft;
//           }
//         },
//         [obj]() mutable {
//           if (!obj->isDragging || !ImGui::IsMouseDown(0))
//             return;

//           auto io = ImGui::GetIO();
//           glm::vec2 newTopLeft =
//             glm::vec2(io.MousePos.x, io.MousePos.y) - obj->dragOffset;
//           // // imToGlmVec2(io.MousePos)
//           glm::vec2 rectSize = obj->bottomRight - obj->topLeft;
//           obj->topLeft = newTopLeft;
//           obj->bottomRight = newTopLeft + rectSize;
//           ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
//           // cursorSet = true;
//         },
//         [obj]() mutable {
//           if (!ImGui::IsMouseReleased(0))
//             return;

//           obj->isDragging = false;
//           // cursorSet = false;
//         }
//       ));
//     }

//     static std::shared_ptr<BehaviorWrapper<T>>
//     createResizable(std::shared_ptr<T> obj) {
//       return wind::share(BehaviorWrapper<T>(
//         "Resizable",
//         [obj]() mutable {
//           if (!ImGui::IsMouseClicked(0))
//             return;

//           auto io = ImGui::GetIO();
//           auto direction =
//             GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x,
//             io.MousePos.y));

//           if (direction == ResizeDirection::None)
//             return;

//           obj->isResizing = true;
//           obj->resizeDir = direction;
// },
// [obj]() mutable {
//           if (!obj->isResizing !!!ImGui::IsMouseDragging(0))
//             return;

//           auto io = ImGui::GetIO();
//           auto direction =
//             GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x,
//             io.MousePos.y));
//           glm::vec2 delta = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
//           // imToGlmVec2(io.MouseDelta);
//           switch (direction) {
//           case ResizeDirection::Top: obj->topLeft.y += delta.y; break;
//           case ResizeDirection::Bottom: obj->bottomRight.y += delta.y; break;
//           case ResizeDirection::Left: obj->topLeft.x += delta.x; break;
//           case ResizeDirection::Right: obj->bottomRight.x += delta.x; break;
//           case ResizeDirection::TopLeft:
//             obj->topLeft.x += delta.x;
//             obj->topLeft.y += delta.y;
//             break;
//           case ResizeDirection::TopRight:
//             obj->bottomRight.x += delta.x;
//             obj->topLeft.y += delta.y;
//             break;
//           case ResizeDirection::BottomLeft:
//             obj->topLeft.x += delta.x;
//             obj->bottomRight.y += delta.y;
//             break;
//           case ResizeDirection::BottomRight:
//             obj->bottomRight.x += delta.x;
//             obj->bottomRight.y += delta.y;
//             break;
//           case ResizeDirection::None:
//           default: break;
//           }
// },
// [obj]() mutable {
//           if (!ImGui::IsMouseReleased(0))
//             return;

//           obj->isResizing = false;
//           obj->resizeDir = ResizeDirection::None;
//           // cursorSet = false;
//         }
//       ));
//     }
//   };

//   template <typename T>
//   class BehaviorManager {
//   public:
//     std::unordered_set<std::shared_ptr<BehaviorWrapper<T>>> behaviors;

//     bool use() {
//       for (std::shared_ptr<BehaviorWrapper<T>> behavior : behaviors) {
//         behavior->use();
//       }
//     }

//     bool addBehavior(std::shared_ptr<BehaviorWrapper<T>> behavior) {
//       behaviors.insert(behavior);
//     }

//     bool removeBehavior(std::shared_ptr<BehaviorWrapper<T>> behavior) {
//       behaviors.erase(behavior);
//     }
//   };
// } // namespace editor::spriteSheetManager

#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <functional>

#include <unordered_set>
#include <memory>

namespace editor::spriteSheetManager {
  enum class ResizeDirection {
    None,
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  template <typename T>
  ResizeDirection
  GetResizeDirection(std::shared_ptr<T> rect, glm::vec2 mousePos) {
    // if (rect == nullptr) {
    //   return ResizeDirection::None;
    // }
    spdlog::info(
      "{} {} {} {}", mousePos.x, rect->topLeft.x, mousePos.y, rect->topLeft.y
    );
    auto padding = 8.0f;
    bool nearLeft = mousePos.x >= rect->topLeft.x - padding &&
                    mousePos.x <= rect->topLeft.x + padding;
    bool nearRight = mousePos.x >= rect->bottomRight.x - padding &&
                     mousePos.x <= rect->bottomRight.x + padding;
    bool nearTop = mousePos.y >= rect->topLeft.y - padding &&
                   mousePos.y <= rect->topLeft.y + padding;
    bool nearBottom = mousePos.y >= rect->bottomRight.y - padding &&
                      mousePos.y <= rect->bottomRight.y + padding;
    if (nearLeft && nearTop)
      return ResizeDirection::TopLeft;
    if (nearRight && nearTop)
      return ResizeDirection::TopRight;
    if (nearLeft && nearBottom)
      return ResizeDirection::BottomLeft;
    if (nearRight && nearBottom)
      return ResizeDirection::BottomRight;
    if (nearTop)
      return ResizeDirection::Top;
    if (nearBottom)
      return ResizeDirection::Bottom;
    if (nearLeft)
      return ResizeDirection::Left;
    if (nearRight)
      return ResizeDirection::Right;

    return ResizeDirection::None;
  };

  template <typename T>
  class BehaviorWrapper {
  public:
    std::string id;
    std::function<void()> start;
    std::function<void()> move;
    std::function<void()> end;
    std::function<void()> action;

    BehaviorWrapper(
      const std::string& id,
      std::function<void()> start,
      std::function<void()> move,
      std::function<void()> end
    )
        : id(id), start(start), move(move), end(end) {
      action = [start, move, end]() {
        start();
        move();
        end();
      };
    }
  };

  template <typename T>
  concept HasSize = requires(T t) {
    { t.topLeft } -> std::convertible_to<glm::vec2>;
    { t.bottomRight } -> std::convertible_to<glm::vec2>;
  };

  template <HasSize T>
  class BehaviorFactory {
  public:
    static std::shared_ptr<BehaviorWrapper<T>>
    createDraggable(std::shared_ptr<T> obj) {
      return wind::share(BehaviorWrapper<T>(
        "Draggable",
        [obj]() mutable {
          if (!ImGui::IsMouseClicked(0))
            return;

          auto io = ImGui::GetIO();
          auto direction =
            GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x, io.MousePos.y));

          if (direction != ResizeDirection::None)
            return;

          if (io.MousePos.x >= obj->topLeft.x &&
              io.MousePos.x <= obj->bottomRight.x &&
              io.MousePos.y >= obj->topLeft.y &&
              io.MousePos.y <= obj->bottomRight.y) {
            obj->isDragging = true;
            obj->dragOffset =
              glm::vec2(io.MousePos.x, io.MousePos.y) - obj->topLeft;
            // imToGlmVec2(io.MousePos) - obj->topLeft;
          }
        },
        [obj]() mutable {
          if (!obj->isDragging || !ImGui::IsMouseDown(0))
            return;

          auto io = ImGui::GetIO();
          glm::vec2 newTopLeft =
            glm::vec2(io.MousePos.x, io.MousePos.y) - obj->dragOffset;
          // // imToGlmVec2(io.MousePos)
          glm::vec2 rectSize = obj->bottomRight - obj->topLeft;
          obj->topLeft = newTopLeft;
          obj->bottomRight = newTopLeft + rectSize;
          ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
          // cursorSet = true;
        },
        [obj]() mutable {
          if (!ImGui::IsMouseReleased(0))
            return;

          obj->isDragging = false;
          // cursorSet = false;
        }
      ));
    };

    static std::shared_ptr<BehaviorWrapper<T>>
    createResizable(std::shared_ptr<T> obj) {
      return wind::share(BehaviorWrapper<T>(
        "Resizable",
        [obj]() mutable {
          if (!ImGui::IsMouseClicked(0))
            return;

          auto io = ImGui::GetIO();
          auto direction =
            GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x, io.MousePos.y));

          if (direction == ResizeDirection::None)
            return;

          // if (io.MousePos.x >= obj->topLeft.x &&
          //     io.MousePos.x <= obj->bottomRight.x &&
          //     io.MousePos.y >= obj->topLeft.y &&
          //     io.MousePos.y <= obj->bottomRight.y) {
          obj->isResizing = true;
          obj->resizeDir = direction;
          // }
        },
        [obj]() mutable {
          if (!obj->isResizing || !ImGui::IsMouseDragging(0))
            return;

          auto io = ImGui::GetIO();
          // auto direction =
          //   GetResizeDirection<T>(obj, glm::vec2(io.MousePos.x,
          //   io.MousePos.y));
          glm::vec2 delta = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
          // imToGlmVec2(io.MouseDelta);
          switch (obj->resizeDir) {
            case ResizeDirection::Top: obj->topLeft.y += delta.y; break;
            case ResizeDirection::Bottom: obj->bottomRight.y += delta.y; break;
            case ResizeDirection::Left: obj->topLeft.x += delta.x; break;
            case ResizeDirection::Right: obj->bottomRight.x += delta.x; break;
            case ResizeDirection::TopLeft:
              obj->topLeft.x += delta.x;
              obj->topLeft.y += delta.y;
              break;
            case ResizeDirection::TopRight:
              obj->bottomRight.x += delta.x;
              obj->topLeft.y += delta.y;
              break;
            case ResizeDirection::BottomLeft:
              obj->topLeft.x += delta.x;
              obj->bottomRight.y += delta.y;
              break;
            case ResizeDirection::BottomRight:
              obj->bottomRight.x += delta.x;
              obj->bottomRight.y += delta.y;
              break;
            case ResizeDirection::None:
            default: break;
          }
        },
        [obj]() mutable {
          if (!ImGui::IsMouseReleased(0))
            return;

          obj->isResizing = false;
          obj->resizeDir = ResizeDirection::None;
          // cursorSet = false;
        }
      ));
    };

    static std::shared_ptr<BehaviorWrapper<T>>
    createDoubleClickable(std::shared_ptr<T> obj, Callback callback) {
      return wind::share(BehaviorWrapper<T>(
        "DoubleClickable",
        []() {},
        [obj, callback]() {
          if (ImGui::IsMouseDoubleClicked(0)) {
            auto mousePos = ImGui::GetIO().MousePos;
            if (mousePos.x >= obj->topLeft.x &&
                mousePos.x <= obj->bottomRight.x &&
                mousePos.y >= obj->topLeft.y &&
                mousePos.y <= obj->bottomRight.y) {
              callback();
            }
          }
        },
        []() {}
      ));
    };

    static std::shared_ptr<BehaviorWrapper<T>>
    createClickable(std::shared_ptr<T> obj, Callback callback) {
      return wind::share(BehaviorWrapper<T>(
        "Clickable",
        []() {},
        [obj, callback]() {
          if (ImGui::IsMouseClicked(0)) {
            auto mousePos = ImGui::GetIO().MousePos;
            if (mousePos.x >= obj->topLeft.x &&
                mousePos.x <= obj->bottomRight.x &&
                mousePos.y >= obj->topLeft.y &&
                mousePos.y <= obj->bottomRight.y) {
              callback();
            }
          }
        },
        []() {}
      ));
    };
  };

  template <typename T>
  class BehaviorManager {
  public:
    std::unordered_set<std::shared_ptr<BehaviorWrapper<T>>> behaviors;

    bool action() {
      for (std::shared_ptr<BehaviorWrapper<T>> behavior : behaviors) {
        behavior->action();
      }
    };

    bool addBehavior(std::shared_ptr<BehaviorWrapper<T>> behavior) {
      behaviors.insert(behavior);
    };

    bool removeBehavior(std::shared_ptr<BehaviorWrapper<T>> behavior) {
      behaviors.erase(behavior);
    };
  };
} // namespace editor::spriteSheetManager
