project(game)

set(SOURCES
  ./app/src/main.cpp
)

add_wind_game(${PROJECT_NAME} "main;"  ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./app/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind)