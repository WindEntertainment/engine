project(editor)

set(HEADERS
  ./include/editor/editor.hpp
  ./include/editor/main.hpp
  ./include/editor/shared/file-picker.hpp
  ./include/editor/shared/menu/menu-item.hpp
  ./include/editor/shared/menu/menu-bar.hpp
  ./include/editor/shared/menu/menu.hpp
  ./include/editor/shared/popup.hpp
  ./include/editor/shared/tab-bar/tab.hpp
  ./include/editor/shared/tab-bar/tab-bar.hpp
  ./include/editor/shared/tab-bar/tab-item.hpp
  ./include/editor/shared/window.hpp
  ./include/editor/sprite-sheet-manager/sprite-sheet-manager.hpp
  ./include/editor/project-manager/project-manager.hpp
  ./include/editor/bundle-manager/bundle-manager.hpp
)

set(SOURCES
  ./src/main.cpp
  ./src/shared/file-picker.cpp
  ./src/shared/menu/menu-item.cpp
  ./src/shared/menu/menu-bar.cpp
  ./src/shared/menu/menu.cpp
  ./src/shared/popup.cpp
  ./src/shared/tab-bar/tab.cpp
  ./src/shared/tab-bar/tab-bar.cpp
  ./src/shared/tab-bar/tab-item.cpp
  ./src/shared/window.cpp
  ./src/sprite-sheet-manager/sprite-sheet-manager.cpp
  ./src/project-manager/project-manager.cpp
  ./src/bundle-manager/bundle-manager.cpp
)

set(BINDINGS
  ./include/bindings/imgui_impl_sdl2.cpp
  ./include/bindings/imgui_impl_sdl2.h
  ./include/bindings/imgui_impl_opengl3.cpp
  ./include/bindings/imgui_impl_opengl3.h
  ./include/bindings/imgui_impl_opengl3_loader.h
)

add_executable(
  ${PROJECT_NAME} ${HEADERS} ${SOURCES} ${BINDINGS}
)

#
# find_package(imgui REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)
# target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils wind-window wind-entry wind-input-system wind-asset-manager ImGuiFileDialog)

find_package(imgui REQUIRED)
find_package(sdl2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(stb REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(portable-file-dialogs REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad portable-file-dialogs::portable-file-dialogs stb::stb imgui::imgui SDL2::SDL2 OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils wind-window wind-entry wind-input-system wind-asset-manager ImGuiFileDialog)

#

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)
