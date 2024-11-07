project(wind)

add_subdirectory(./entry/)
add_subdirectory(./window/)
add_subdirectory(./event-manager/)
add_subdirectory(./renderer/)
add_subdirectory(./asset-pipeline/)
add_subdirectory(./input-system/)
add_subdirectory(./utils/)

add_library(${PROJECT_NAME} STATIC engine.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-entry)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-pipeline)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-event-manager)
