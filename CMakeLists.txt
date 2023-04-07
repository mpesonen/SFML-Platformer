cmake_minimum_required(VERSION 3.16)

project(sfml-platformer VERSION 0.01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Extra SFML config
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(SFML_OS_MACOSX ON)

set(EXECUTABLE_NAME sfml-platformer)
include(FetchContent)

set(EXECUTABLE_SOURCES
    "main.cpp"
    "brick.cpp"
    "entity.cpp"
    "game.cpp"
    "map.cpp"
    "player.cpp")

set(EXECUTABLE_HEADERS
    "brick.hpp"
    "constants.hpp"
    "entity.hpp"
    "game.hpp"
    "map.hpp"
    "player.hpp")

add_executable(${EXECUTABLE_NAME}
    ${EXECUTABLE_SOURCES}
    ${EXECUTABLE_HEADERS})

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG ea4c448a85fc1a93c71431faf4b4f12efcfe0976 # Master on April 6th 2023 - about version 3.0.0?
    OVERRIDE_FIND_PACKAGE
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_SOURCE_DIR}/include)
link_directories(${SFML_BINARY_DIR}/lib)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nlohmann_json)

# Copy assets
file(COPY maps DESTINATION ${CMAKE_BINARY_DIR})
file(COPY fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
    nlohmann_json::nlohmann_json)
