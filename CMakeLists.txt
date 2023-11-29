cmake_minimum_required(VERSION 3.20)

project(SEU-Compiler-Labwork)

include_directories(./include)

add_executable(lexical_analyzer src/lexical_analyzer.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)