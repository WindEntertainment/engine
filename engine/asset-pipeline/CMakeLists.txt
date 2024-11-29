project(wind-asset-pipeline)

set(HEADERS
    ./include/wind/asset-pipeline/asset-manager.hpp
    ./include/wind/asset-pipeline/asset-bundler.hpp
    ./include/wind/asset-pipeline/asset-bundler-error.hpp
    ./include/wind/asset-pipeline/consts.hpp
    
    ./include/wind/asset-pipeline/pipes/pipe.hpp
    ./include/wind/asset-pipeline/pipes/pipes-register.hpp
    
    ./include/wind/asset-pipeline/pipes/default-pipe.hpp
    ./include/wind/asset-pipeline/pipes/shader-pipe.hpp
    ./include/wind/asset-pipeline/pipes/img-pipe.hpp
)

set(SOURCES
    ./src/asset-manager.cpp
    ./src/asset-bundler.cpp
    ./src/clear-cache.cpp
    ./src/compile-directory.cpp
    ./src/compile-file.cpp
    ./src/export-directory.cpp
    ./src/link-directory.cpp
    ./src/preprocessing.cpp
    ./src/processing.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)

find_package(stb REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC stb::stb)

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)