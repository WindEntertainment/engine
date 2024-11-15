project(wind-entry)

set(HEADERS
    ./include/wind/wind.hpp
)

set(SOURCES
    ./src/wind.cpp
    ./src/default-res.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
