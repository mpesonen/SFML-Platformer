cmake_minimum_required(VERSION 3.16)

project(sfml-platformer VERSION 0.01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Extra SFML config
set(CMAKE_OSX_ARCHITECTURES "${CMAKE_SYSTEM_PROCESSOR}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SFML_OS_MACOSX ON)
endif()
set(SFML_BUILD_AUDIO ON)

set(EXECUTABLE_NAME sfml-platformer)
include(FetchContent)

set(EXECUTABLE_SOURCES
    "main.cpp"
    "brick.cpp"
    "entity.cpp"
    "game.cpp"
    "map.cpp"
    "player.cpp"
    "interactions.cpp"
    "coin.cpp"
    "sharedresources.cpp")

set(EXECUTABLE_HEADERS
    "brick.hpp"
    "constants.hpp"
    "entity.hpp"
    "game.hpp"
    "map.hpp"
    "player.hpp"
    "interactions.hpp"
    "coin.hpp"
    "sharedresources.hpp")

add_executable(${EXECUTABLE_NAME}
    ${EXECUTABLE_SOURCES}
    ${EXECUTABLE_HEADERS})

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG fb1cfdc48d37dbb6ce383311ae5805c1f98db5d1 # Master on May 4th 2023 - about version 3.0.0?
    )
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
file(COPY audio DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    nlohmann_json::nlohmann_json)
