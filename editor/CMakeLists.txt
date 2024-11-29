project(editor)

set(HEADERS
  # ./app/include/editor/editor.hpp
  # ./app/include/editor/main.hpp
  # ./app/include/editor/shared/file-picker.hpp
  # ./app/include/editor/shared/menu/menu-item.hpp
  # ./app/include/editor/shared/menu/menu-bar.hpp
  # ./app/include/editor/shared/menu/menu.hpp
  # ./app/include/editor/shared/popup.hpp
  # ./app/include/editor/shared/tab-bar/tab.hpp
  # ./app/include/editor/shared/tab-bar/tab-bar.hpp
  # ./app/include/editor/shared/image.hpp
  # ./app/include/editor/shared/window.hpp
  # ./app/include/editor/sprite-sheet/cell.hpp
  # ./app/include/editor/sprite-sheet/cells-manager.hpp
  # ./app/include/editor/sprite-sheet/events.hpp
  # ./app/include/editor/sprite-sheet/file.hpp
  # ./app/include/editor/sprite-sheet/behavior.hpp
  # ./app/include/editor/sprite-sheet/files-manager.hpp
  # ./app/include/editor/sprite-sheet/sprite-sheet-manager.hpp
  # ./app/include/editor/project-manager/project-manager.hpp
  # ./app/include/editor/bundle-manager/bundle-manager.hpp
  # ./app/include/editor/components.hpp
)

set(SOURCES
  ./app/src/main.cpp
  # ./app/src/shared/file-picker.cpp
  # ./app/src/shared/menu/menu-item.cpp
  # ./app/src/shared/menu/menu-bar.cpp
  # ./app/src/shared/menu/menu.cpp
  # ./app/src/shared/popup.cpp
  # ./app/src/shared/tab-bar/tab.cpp
  # ./app/src/shared/tab-bar/tab-bar.cpp
  # ./app/src/shared/image.cpp
  # ./app/src/shared/window.cpp
  # ./app/src/sprite-sheet/cell.cpp
  # ./app/src/sprite-sheet/cells-manager.cpp
  # ./app/src/sprite-sheet/events.cpp
  # ./app/src/sprite-sheet/file.cpp
  # ./app/src/sprite-sheet/files-manager.cpp
  # ./app/src/sprite-sheet/sprite-sheet-manager.cpp
  # ./app/src/project-manager/project-manager.cpp
  # ./app/src/bundle-manager/bundle-manager.cpp
)

# set(BINDINGS
#   ./app/include/bindings/imgui_impl_sdl2.cpp
#   ./app/include/bindings/imgui_impl_sdl2.h
#   ./app/include/bindings/imgui_impl_opengl3.cpp
#   ./app/include/bindings/imgui_impl_opengl3.h
#   ./app/include/bindings/imgui_impl_opengl3_loader.h
# )

add_wind_game(${PROJECT_NAME} "main;" ${HEADERS} ${SOURCES} ${BINDINGS})

find_package(spdlog REQUIRED)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./app/include/)
