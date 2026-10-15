target_sources(
    libbx
    PRIVATE
        c_family.cpp
        exceptions.cpp
        executor.cpp
        gcc.cpp
        main.cpp
        rule.cpp
        step.cpp
        toolchain.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/build.hpp
        buildx/c_family.hpp
        buildx/exceptions.hpp
        buildx/executor.hpp
        buildx/gcc.hpp
        buildx/rule.hpp
        buildx/step.hpp
        buildx/target.hpp
        buildx/this_build.hpp
        buildx/toolchain.hpp
)

target_link_libraries(libbx PUBLIC Boost::process Boost::cobalt)
target_link_libraries(bx PUBLIC libbx)
