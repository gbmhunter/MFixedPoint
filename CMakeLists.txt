# TravisCI is running cmake v2.8.7
cmake_minimum_required(VERSION 2.8.7)
project(MFixedPoint)

add_definitions(-std=c++11)

option(BUILD_DEPENDENCIES "If set to ON, dependencies will be downloaded and built as part of the build process." ON)

if (BUILD_DEPENDENCIES)
    message("BUILD_DEPENDENCIES=ON, dependencies will be downloaded and built automatically.")
    # EXTERNAL_INSTALL_LOCATION is used by external projects, except for gtest
    include(ExternalProject)
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
else ()
    message("BUILD_DEPENDENCIES=OFF, dependencies have to be downloaded, built and installed manually.")
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

include_directories(../)
include_directories(include)

add_subdirectory(src)
add_subdirectory(test)