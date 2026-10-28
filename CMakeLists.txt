cmake_minimum_required(VERSION 4.0)

project(buildx)

option(ENABLE_STATIC OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

find_package(ECM REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS Process Cobalt REQUIRED)

include(cmake/bundle.cmake)
include(cmake/archive.cmake)

include(KDEClangFormat)
file(GLOB_RECURSE CLANG_FORMAT_FILES src/*.cpp  src/*.hpp)
kde_clang_format(${CLANG_FORMAT_FILES})

add_subdirectory(src)
