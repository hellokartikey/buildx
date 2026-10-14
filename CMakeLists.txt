cmake_minimum_required(VERSION 4.0)

project(buildx)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

find_package(Boost COMPONENTS Process Cobalt)

add_library(libbx)
set_target_properties(libbx PROPERTIES OUTPUT_NAME bx)

add_executable(bx src/main.cpp)

add_subdirectory(src)
