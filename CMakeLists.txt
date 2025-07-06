cmake_minimum_required(VERSION 3.30)
project(dominoCPP)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_PATH "${PROJECT_SOURCE_DIR}/raylib")

include_directories(${RAYLIB_PATH}/include)

link_directories(${RAYLIB_PATH}/lib)

add_executable(${PROJECT_NAME} main.cpp
        graphics.h)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)