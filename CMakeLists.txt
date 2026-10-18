cmake_minimum_required(VERSION 4.0)

project(buildx)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS Process Cobalt REQUIRED)

add_library(libbx)
set_target_properties(libbx PROPERTIES OUTPUT_NAME bx)

add_executable(bx src/build.cpp)

add_subdirectory(src)
