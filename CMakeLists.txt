cmake_minimum_required(VERSION 3.20)

project(Acorn VERSION 1.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# macOS architecture
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "" FORCE)
endif()

# Output directories
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_OSX_ARCHITECTURES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)

# ============================================================================
# Vendor Libraries
# ============================================================================

# ImGui
add_subdirectory(Acorn/vendor/imgui)

# GLFW
add_subdirectory(Acorn/vendor/glfw)

# yaml-cpp
add_subdirectory(Acorn/vendor/yaml-cpp)

# stb_image
file(WRITE ${CMAKE_BINARY_DIR}/stb_image_impl.cpp
"#define STB_IMAGE_IMPLEMENTATION
#include \"stb_image.h\"
")
add_library(stb STATIC ${CMAKE_BINARY_DIR}/stb_image_impl.cpp)
target_include_directories(stb PUBLIC Acorn/vendor/stb)

# Vulkan
find_package(Vulkan REQUIRED)
if(APPLE)
    find_library(MOLTENVK_LIBRARY MoltenVK 
        PATHS /opt/homebrew/lib /usr/local/lib 
        REQUIRED)
endif()

# ============================================================================
# Acorn Engine Library
# ============================================================================

file(GLOB_RECURSE ACORN_SOURCES
    Acorn/src/Acorn/*.cpp
    Acorn/src/Acorn/*.h
)

add_library(Acorn STATIC ${ACORN_SOURCES})

target_compile_features(Acorn PUBLIC cxx_std_20)

target_include_directories(Acorn PUBLIC
    Acorn/src
    Acorn/vendor/imgui
    Acorn/vendor/glfw/include
    Acorn/vendor/glm
    Acorn/vendor/spdlog/include
    Acorn/vendor/stb
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(Acorn PUBLIC
    ImGui
    GLFW
    Vulkan::Vulkan
    yaml-cpp
    stb
)

# Platform-specific
if(APPLE)
    target_compile_definitions(Acorn PUBLIC 
        AC_PLATFORM_MACOS
        VK_USE_PLATFORM_METAL_EXT
    )
    target_link_libraries(Acorn PUBLIC
        ${MOLTENVK_LIBRARY}
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework Metal"
        "-framework QuartzCore"
    )
endif()

# Build configs
target_compile_definitions(Acorn PUBLIC
    $<$<CONFIG:Debug>:AC_DEBUG;AC_ENABLE_ASSERTS>
    $<$<CONFIG:Release>:AC_RELEASE>
    $<$<CONFIG:Dist>:AC_DIST>
)

# ============================================================================
# AcornApp Executable
# ============================================================================

file(GLOB_RECURSE ACORNAPP_SOURCES
    AcornApp/src/*.cpp
    AcornApp/src/*.h
)

add_executable(AcornApp ${ACORNAPP_SOURCES})

target_compile_features(AcornApp PRIVATE cxx_std_20)

target_include_directories(AcornApp PRIVATE
    AcornApp/src
)

target_link_libraries(AcornApp PRIVATE
    Acorn
)