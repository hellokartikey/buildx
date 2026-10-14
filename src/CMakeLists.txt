target_sources(
    libbx
    PRIVATE
        exceptions.cpp
        gcc.cpp
        rule.cpp
        step.cpp
        toolchain.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/c_family.hpp
        buildx/exceptions.hpp
        buildx/gcc.hpp
        buildx/rule.hpp
        buildx/step.hpp
        buildx/target.hpp
        buildx/toolchain.hpp
)

target_link_libraries(libbx PUBLIC Boost::process Boost::cobalt)
target_link_libraries(bx PUBLIC libbx)
