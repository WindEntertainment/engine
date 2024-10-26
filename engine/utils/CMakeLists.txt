project(wind-utils)

set(HEADERS
    ./include/utils/includes.hpp
    ./include/utils/utils.hpp
    ./include/utils/yaml-utils.hpp
)

set(SOURCES
    ./src/utils.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
