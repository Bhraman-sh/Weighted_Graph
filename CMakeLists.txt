cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(weighted_graph VERSION 1.0)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(weighted_graph main.c ${SOURCES})
target_include_directories(weighted_graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(weighted_graph PUBLIC ${GLFW})
