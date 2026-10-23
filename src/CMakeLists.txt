target_sources(
    libbx
    PRIVATE
        c_family.cpp
        context.cpp
        exceptions.cpp
        executable.cpp
        executor.cpp
        gcc.cpp
        library.cpp
        phony.cpp
        main.cpp
        rule.cpp
        step.cpp
        target.cpp
        toolchain.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/build.hpp
        buildx/cc.hpp
        buildx/c_family.hpp
        buildx/context.hpp
        buildx/exceptions.hpp
        buildx/executable.hpp
        buildx/executor.hpp
        buildx/gcc.hpp
        buildx/library.hpp
        buildx/phony.hpp
        buildx/rule.hpp
        buildx/step.hpp
        buildx/target.hpp
        buildx/this_build.hpp
        buildx/toolchain.hpp
        buildx/view.hpp
)

target_link_libraries(libbx PRIVATE Boost::process Boost::cobalt)
target_link_libraries(bx PRIVATE libbx)
