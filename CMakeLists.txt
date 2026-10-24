cmake_minimum_required(VERSION 4.0)

project(buildx)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

include(cmake/bundle.cmake)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS Process Cobalt REQUIRED)

find_package(LibArchive REQUIRED)

add_subdirectory(src)
