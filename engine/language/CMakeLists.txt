project(wind-language)

set(HEADERS
    ./include/wind/language/language.hpp
)

set(SOURCES
    ./src/language.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)