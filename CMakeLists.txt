cmake_minimum_required(VERSION 3.30)
project(dominoCPP)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_PATH "${PROJECT_SOURCE_DIR}/raylib")
include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

set(JSON_PATH "${PROJECT_SOURCE_DIR}/json")
include_directories(${JSON_PATH}/include)

add_executable(${PROJECT_NAME} main.cpp
        parameters.h
        button.h
        button.cpp
        player.cpp
        player.h
        list.h
        tile.h
        tile.cpp
        list.cpp
        game.h
        game.cpp
        set.cpp
        set.h
        field.cpp
        field.h
        menu.cpp
        menu.h
        records.cpp
        records.h
        statistics.cpp
        statistics.h
        bot.cpp
        bot.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)