add_library(libbx)
set_target_properties(libbx PROPERTIES OUTPUT_NAME bx)

target_sources(
    libbx
    PRIVATE
        c_family.cpp
        command.cpp
        context.cpp
        exceptions.cpp
        executable.cpp
        executor.cpp
        gcc.cpp
        gxx.cpp
        library.cpp
        main.cpp
        phony.cpp
        rule.cpp
        script.cpp
        step.cpp
        system_library.cpp
        target.cpp
        toolchain.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/build.hpp
        buildx/cc.hpp
        buildx/c_family.hpp
        buildx/command.hpp
        buildx/context.hpp
        buildx/cxx.hpp
        buildx/exceptions.hpp
        buildx/executable.hpp
        buildx/executor.hpp
        buildx/gcc.hpp
        buildx/gxx.hpp
        buildx/library.hpp
        buildx/phony.hpp
        buildx/rule.hpp
        buildx/script.hpp
        buildx/step.hpp
        buildx/system_library.hpp
        buildx/target.hpp
        buildx/this_build.hpp
        buildx/toolchain.hpp
        buildx/view.hpp
)


target_link_libraries(libbx PRIVATE Boost::process Boost::cobalt)
bundle_static_library(libbx bx_bundle)

set(HEADERS_NAME "bx.tar")
set(HEADERS_FILE "${CMAKE_BINARY_DIR}/${HEADERS_NAME}")
get_target_property(ALL_HEADERS libbx HEADER_SET_HEADERS)

find_program(TAR_PROGRAM tar REQUIRED)
add_custom_target(
    ${HEADERS_NAME}
    ALL
    COMMAND
        ${TAR_PROGRAM}
        cPf ${HEADERS_FILE}
        --transform="s|^.*buildx/|include/buildx/|"
        ${ALL_HEADERS}
    COMMENT "Archiving ${LIBBX_NAME} headers ${HEADERS_NAME}"
    DEPENDS ${ALL_HEADERS}
)

set(LIBBX_NAME "${CMAKE_STATIC_LIBRARY_PREFIX}bx${CMAKE_STATIC_LIBRARY_SUFFIX}")

add_executable(bx build.cpp)
target_link_libraries(bx PRIVATE libbx)
target_compile_definitions(
    bx
    PRIVATE
        -DLIBBX_FILE="$<TARGET_FILE:bx_bundle>"
        -DLIBBX_NAME="${LIBBX_NAME}"
        -DHEADERS_FILE="${HEADERS_FILE}"
        -DHEADERS_NAME="${HEADERS_NAME}"
)
