enable_testing()
find_package (Threads)

# The main header files do not actually have to be added here, but
# this helps CLion recognize the header files as being part of a
# project and allows auto-complete to work correctly.
file(GLOB_RECURSE MFixedPoint_HEADERS
        "${CMAKE_SOURCE_DIR}/include/*.hpp")

file(GLOB_RECURSE MFixedPointTests_SRC
        "*.cpp"
        "*.hpp"
        )

add_executable (MFixedPointTests ${MFixedPoint_HEADERS} ${MFixedPointTests_SRC})
add_dependencies (MFixedPointTests MUnitTest_Project)

if(COVERAGE)
    set_target_properties(MFixedPointTests PROPERTIES COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    set_target_properties(MFixedPointTests PROPERTIES LINK_FLAGS "-coverage -lgcov")
endif ()

target_link_libraries(MFixedPointTests LINK_PUBLIC MUnitTest ${CMAKE_THREAD_LIBS_INIT})

add_custom_target(
    run_unit_tests ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/MFixedPointTests.touch MFixedPointTests)

add_custom_command(         
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/MFixedPointTests.touch
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/MFixedPointTests)

# Target name, executable that runs unit tests, output directory
if(COVERAGE)
    setup_target_for_coverage(${PROJECT_NAME}_coverage MFixedPointTests coverage)
endif()