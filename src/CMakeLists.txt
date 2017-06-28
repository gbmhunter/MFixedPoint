file(GLOB_RECURSE MFixedPoint_SRC
        "*.cpp")

file(GLOB_RECURSE MFixedPoint_HEADERS
        "../include/*.hpp")

add_library(MFixedPoint ${MFixedPoint_SRC} ${MFixedPoint_HEADERS})