project(wind-renderer)

set(HEADERS
    ./include/wind/renderer/command-buffer.hpp
    ./include/wind/renderer/material.hpp
    ./include/wind/renderer/mesh.hpp
    ./include/wind/renderer/object.hpp
    ./include/wind/renderer/shader.hpp
    ./include/wind/renderer/render_context.hpp
    ./include/wind/renderer/texture.hpp
    ./include/wind/renderer/assets.hpp
    ./include/wind/renderer/camera.hpp
    ./include/wind/renderer/sprite.hpp
)

set(SOURCES
    ./src/command-buffer.cpp
    ./src/shader.cpp
    ./src/material.cpp
    ./src/mesh.cpp
    ./src/render_context.cpp
    ./src/texture.cpp
    ./src/assets.cpp
    ./src/camera.cpp
    ./src/sprite.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-pipeline)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)