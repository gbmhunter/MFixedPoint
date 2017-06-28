file(GLOB_RECURSE MFixedPoint_SRC
        "*.cpp")

file(GLOB_RECURSE MFixedPoint_HEADERS
        "../include/*.hpp")

add_library(MFixedPoint ${MFixedPoint_SRC} ${MFixedPoint_HEADERS})

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/lib
install(TARGETS MFixedPoint DESTINATION lib)

# On Linux, "sudo make install" will typically copy the 
# folder into /usr/local/include
install(DIRECTORY ../include/MFixedPoint DESTINATION include)