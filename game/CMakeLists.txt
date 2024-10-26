project(game)

set(HEADERS
  ./include/game/logger.hpp
)

set(SOURCES
  ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-entry)
# target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-manager)