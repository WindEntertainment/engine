project(wind-event-manager)

set(HEADERS
  ./include/wind/event-manager/event-manager.hpp
)

set(SOURCES
  ./src/event-manager.cpp
)


add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
