add_library(libbx)
set_target_properties(libbx PROPERTIES OUTPUT_NAME bx)

target_sources(
    libbx
    PRIVATE
        c_mixins.cpp
        clang_cc.cpp
        clang_cxx.cpp
        gnu_ar.cpp
        gnu_cc.cpp
        gnu_cxx.cpp
        llvm_ar.cpp

        toolchain.cpp
        archive_tool.cpp
        shared_tool.cpp
        static_tool.cpp

        context.cpp
        exceptions.cpp
        executor.cpp
        rule.cpp
        step.cpp
        main.cpp

        target.cpp
        command.cpp
        executable.cpp
        library.cpp
        phony.cpp
        script.cpp
        system_library.cpp

        clang.cpp
        clangxx.cpp
        gcc.cpp
        gxx.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/tool/c_mixins.hpp
        buildx/tool/gnu_ar.hpp
        buildx/tool/clang_cc.hpp
        buildx/tool/clang_cxx.hpp
        buildx/tool/gnu_cc.hpp
        buildx/tool/gnu_cxx.hpp
        buildx/tool/llvm_ar.hpp

        buildx/toolchain.hpp
        buildx/archive_tool.hpp
        buildx/shared_tool.hpp
        buildx/static_tool.hpp

        buildx/context.hpp
        buildx/exceptions.hpp
        buildx/executor.hpp
        buildx/rule.hpp
        buildx/step.hpp
        buildx/this_build.hpp
        buildx/view.hpp

        buildx/target.hpp
        buildx/command.hpp
        buildx/executable.hpp
        buildx/library.hpp
        buildx/phony.hpp
        buildx/script.hpp
        buildx/system_library.hpp

        buildx/clang.hpp
        buildx/clangxx.hpp
        buildx/gcc.hpp
        buildx/gxx.hpp

        buildx/build.hpp
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
