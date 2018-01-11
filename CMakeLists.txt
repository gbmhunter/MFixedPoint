# TravisCI is running cmake v2.8.7
cmake_minimum_required(VERSION 2.8.7)
project(MFixedPoint)

add_definitions(-std=c++11)

# Custom CMake module path that is part if this repo
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

include(CodeCoverage)

set(HEADER_ONLY true)

#=================================================================================================#
#========================================= INPUT ARGUMENTS =======================================#
#=================================================================================================#

option(BUILD_DEPENDENCIES "If set to ON, dependencies will be downloaded and built as part of the build process." ON)
if (BUILD_DEPENDENCIES)
    message("BUILD_DEPENDENCIES=ON, dependencies will be downloaded and built automatically.")
    # EXTERNAL_INSTALL_LOCATION is used by external projects, except for gtest
    include(ExternalProject)
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
else ()
    message("BUILD_DEPENDENCIES=OFF, dependencies have to be downloaded, built and installed manually.")
endif ()

option(BUILD_TESTS "If set to true, unit tests will be build as part of make all." TRUE)
if (BUILD_TESTS)
    message("BUILD_TESTS=TRUE, unit tests will be built.")
else ()
    message("BUILD_TESTS=FALSE, unit tests will NOT be built.")
endif ()

option(COVERAGE "If set to true, coverage will be enabled." FALSE)
if (COVERAGE)
    message("COVERAGE=TRUE, coverage will be enabled.")
else ()
    message("COVERAGE=FALSE, coverage will NOT be enabled.")
endif ()

#=================================================================================================#
#============================================ MUnitTest ==========================================#
#=================================================================================================#

if (BUILD_DEPENDENCIES)
    ExternalProject_Add(MUnitTest_Project
            GIT_REPOSITORY https://github.com/mbedded-ninja/MUnitTest
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
            )
    include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
    link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)
endif ()

#include_directories(../)
include_directories(include)

if(!HEADER_ONLY)
    add_subdirectory(src)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
add_subdirectory(benchmark)

add_subdirectory(example)

# On Linux, "sudo make install" will typically copy the 
# folder into /usr/local/include
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/MFixedPoint DESTINATION include)

   