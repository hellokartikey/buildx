target_sources(libbx
    PRIVATE
        exceptions.cpp
        rule.cpp

    PUBLIC FILE_SET HEADERS FILES
        buildx/exceptions.hpp
        buildx/rule.hpp
)
