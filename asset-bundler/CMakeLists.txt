project(wind-asset-bundler)

set(SOURCES
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE wind)

find_package(cxxopts REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts::cxxopts)