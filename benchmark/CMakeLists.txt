file(GLOB_RECURSE MFixedPoint_Benchmark_SRC
        "*.cpp"
        "*.hpp")

add_executable (MFixedPoint_Benchmark ${MFixedPoint_Benchmark_SRC})


target_link_libraries(MFixedPoint_Benchmark LINK_PUBLIC MFixedPoint)