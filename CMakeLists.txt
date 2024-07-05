cmake_minimum_required(VERSION 3.5)

project(todoApp)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

include_directories(
    include/controller
    include/model
    include/tui
    json-develop/single_include/
)

file(
    GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/controller/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/model/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/tui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
