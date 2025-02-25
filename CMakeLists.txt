cmake_minimum_required(VERSION 3.28)
project(untitled1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(untitled1 main.cpp
        Objects/Player.h
        Global.h
        TileManager/TileMap.h
        Objects/GameObject.h
        GameEngine.cpp
        GameEngine.h
        Objects/GameObject.cpp
        Objects/Player.cpp
        Managers/ObjectManager.cpp
        Managers/ObjectManager.h
        TileManager/TileMap.cpp
)
target_compile_features(untitled1 PRIVATE cxx_std_17)
target_link_libraries(untitled1 PRIVATE SFML::Graphics)