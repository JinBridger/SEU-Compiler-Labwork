cmake_minimum_required(VERSION 3.20)

project(SEU-Compiler-Labwork)

include_directories(./include)

add_executable(jlex src/jlex.cpp)
target_sources(jlex PRIVATE src/user_function.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)