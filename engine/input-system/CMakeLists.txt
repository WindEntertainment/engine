project(wind-input-system)

set(HEADERS
    ./include/wind/input-system/input-system.hpp
    ./include/wind/input-system/mouse-context.hpp
    ./include/wind/input-system/keyboard-context.hpp
    ./include/wind/input-system/context.hpp
    ./include/wind/input-system/keys.hpp
    ./include/wind/input-system/trigger.hpp
    ./include/wind/input-system/error.hpp

)

set(SOURCES
    ./src/input-system.cpp
    ./src/triggers/keycode-triggers.cpp
    ./src/triggers/grouped-triggers.cpp
    ./src/context/mouse-context.cpp
    ./src/context/keyboard-context.cpp
    ./src/context/keys.cpp
    ./src/triggers/trigger.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils wind-window)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-pipeline)

# extrenal depencencies

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)