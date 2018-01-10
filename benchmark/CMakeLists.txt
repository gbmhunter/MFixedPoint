file(GLOB_RECURSE MFixedPoint_Benchmark_SRC
        "*.cpp"
        "*.hpp")

add_executable (MFixedPoint_Benchmark ${MFixedPoint_Benchmark_SRC})
target_compile_options(MFixedPoint_Benchmark PUBLIC -Wall)

# target_link_libraries(MFixedPoint_Benchmark LINK_PUBLIC MFixedPoint)

add_custom_target(
    fake_target_to_run_benchmark ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/fake_file MFixedPoint_Benchmark)

add_custom_command(         
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fake_file   
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/MFixedPoint_Benchmark)