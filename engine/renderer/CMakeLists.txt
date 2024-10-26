project(wind-renderer)

set(HEADERS
    ./include/wind/renderer/command-buffer.hpp
    ./include/wind/renderer/material.hpp
    ./include/wind/renderer/mesh.hpp
    ./include/wind/renderer/object.hpp
    ./include/wind/renderer/shader.hpp
    ./include/wind/renderer/render_context.hpp
)

set(SOURCES
    ./src/command-buffer.cpp
    ./src/shader.cpp
    ./src/material.cpp
    ./src/mesh.cpp
    ./src/render_context.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)