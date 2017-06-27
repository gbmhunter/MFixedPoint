file(GLOB_RECURSE MFixedPointTests_SRC
        "*.cpp"
        "*.hpp"
        )

add_executable (MFixedPointTests ${MFixedPointTests_SRC})


target_link_libraries(MFixedPointTests LINK_PUBLIC MFixedPoint)