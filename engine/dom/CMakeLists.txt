project(wind-dom)

set(HEADERS
    ./include/wind/dom/attributes/base.hpp
    ./include/wind/dom/attributes/div.hpp
    ./include/wind/dom/attributes/checkbox.hpp
    ./include/wind/dom/attributes/input.hpp
    ./include/wind/dom/attributes/root.hpp
    ./include/wind/dom/attributes/select.hpp
    ./include/wind/dom/attributes/text.hpp
    ./include/wind/dom/attributes/index.hpp

    ./include/wind/dom/dom/dom.hpp
    ./include/wind/dom/dom/shared.hpp
    ./include/wind/dom/dom/index.hpp
    ./include/wind/dom/dom/components/root.hpp
    ./include/wind/dom/dom/components/element.hpp
    ./include/wind/dom/dom/components/div.hpp
    ./include/wind/dom/dom/components/text.hpp
    ./include/wind/dom/dom/components/input.hpp
    ./include/wind/dom/dom/components/checkbox.hpp
    ./include/wind/dom/dom/components/select.hpp
    ./include/wind/dom/dom/components/index.hpp

    ./include/wind/dom/shadow-dom/shadow-dom.hpp
    ./include/wind/dom/shadow-dom/pool-manager.hpp
    ./include/wind/dom/shadow-dom/diff.hpp
    ./include/wind/dom/shadow-dom/index.hpp
    ./include/wind/dom/shadow-dom/shared.hpp
    ./include/wind/dom/shadow-dom/components/root.hpp
    ./include/wind/dom/shadow-dom/components/div.hpp
    ./include/wind/dom/shadow-dom/components/text.hpp
    ./include/wind/dom/shadow-dom/components/input.hpp
    ./include/wind/dom/shadow-dom/components/checkbox.hpp
    ./include/wind/dom/shadow-dom/components/select.hpp
    ./include/wind/dom/shadow-dom/components/index.hpp

    ./include/wind/dom/utils/index.hpp
    ./include/wind/dom/utils/utils.hpp
)

set(SOURCES
    ./src/dom/dom.cpp
    ./src/dom/components/root.cpp
    ./src/dom/components/element.cpp
    ./src/dom/components/div.cpp
    ./src/dom/components/text.cpp
    ./src/dom/components/input.cpp
    ./src/dom/components/checkbox.cpp
    ./src/dom/components/select.cpp

    ./src/shadow-dom/shadow-dom.cpp
    ./src/shadow-dom/pool-manager.cpp
    ./src/shadow-dom/diff.cpp
    ./src/shadow-dom/components/root.cpp
    ./src/shadow-dom/components/div.cpp
    ./src/shadow-dom/components/text.cpp
    ./src/shadow-dom/components/input.cpp
    ./src/shadow-dom/components/checkbox.cpp
    ./src/shadow-dom/components/select.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils wind-renderer wind-input-system)

# extrenal depencencies
