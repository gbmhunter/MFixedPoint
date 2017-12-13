file(GLOB_RECURSE MFixedPoint_SRC
        "*.cpp")

file(GLOB_RECURSE MFixedPoint_HEADERS
        "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_library(MFixedPoint ${MFixedPoint_SRC} ${MFixedPoint_HEADERS})

if(COVERAGE)
        set_target_properties(MFixedPoint PROPERTIES COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
        set_target_properties(MFixedPoint PROPERTIES LINK_FLAGS "-coverage -lgcov")
endif ()

target_include_directories(MFixedPoint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/lib
install(TARGETS MFixedPoint DESTINATION lib)

# On Linux, "sudo make install" will typically copy the 
# folder into /usr/local/include
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/MFixedPoint DESTINATION include)