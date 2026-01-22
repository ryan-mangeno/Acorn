cmake_minimum_required(VERSION 3.20)

project(Acorn
    VERSION 1.0
    LANGUAGES CXX
)

# ------------------------------------------------------------------
# Global settings 
# ------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to x64 on macOS if not specified
if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# Output directory 
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_OSX_ARCHITECTURES}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)


if(APPLE)
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release Dist)

# Dist config (maps to Release + extra optimizations)
if(CMAKE_BUILD_TYPE STREQUAL "Dist")
    add_compile_definitions(DIST_BUILD)
    add_compile_options(-O3)
endif()


# add subprojects
add_subdirectory("Acorn/AcornApp")
add_subdirectory("Acorn/AcornHeadless")