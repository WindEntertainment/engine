project(wind-dom)

set(HEADERS
    ./include/wind/dom/dom.hpp
    ./include/wind/dom/shadow-dom.hpp
)

set(SOURCES
    ./src/dom.cpp
    ./src/shadow-dom.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils wind-renderer wind-input-system)

# extrenal depencencies
