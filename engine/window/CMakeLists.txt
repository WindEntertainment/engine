project(wind-window)

set(HEADERS
    ./include/wind/window/window.hpp
)

set(SOURCES
    ./src/window.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# internal
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main)
