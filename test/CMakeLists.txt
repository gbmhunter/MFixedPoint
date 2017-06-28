file(GLOB_RECURSE MFixedPointTests_SRC
        "*.cpp"
        "*.hpp"
        )

add_executable (MFixedPointTests ${MFixedPointTests_SRC})
add_dependencies (MFixedPointTests MUnitTest_Project)

target_link_libraries(MFixedPointTests LINK_PUBLIC MFixedPoint MUnitTest)

add_custom_target(
    fake_target_to_run_unit_tests ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/fake_file MFixedPointTests)

add_custom_command(         
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fake_file   
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/MFixedPointTests)