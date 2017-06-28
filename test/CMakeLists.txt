file(GLOB_RECURSE MFixedPointTests_SRC
        "*.cpp"
        "*.hpp"
        )

add_executable (MFixedPointTests ${MFixedPointTests_SRC})
add_dependencies (MFixedPointTests MUnitTest_Project)

target_link_libraries(MFixedPointTests LINK_PUBLIC MFixedPoint MUnitTest)