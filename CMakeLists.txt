cmake_minimum_required(VERSION 3.20)

project(Acorn
    VERSION 1.0
    LANGUAGES CXX
)

# -------------------------------------------------
# C++ settings
# -------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# macOS arch
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "" FORCE)
endif()

# -------------------------------------------------
# Output layout
# -------------------------------------------------
set(OUTPUT_DIR
    ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_OSX_ARCHITECTURES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)

# -------------------------------------------------
# Warnings
# -------------------------------------------------
if(APPLE)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# -------------------------------------------------
# Vendor libraries
# -------------------------------------------------
add_subdirectory(Acorn/vendor/imgui)
add_subdirectory(Acorn/vendor/yaml-cpp)
add_subdirectory(Acorn/vendor/glfw)

# -------------------------------------------------
# Vulkan / MoltenVK
# -------------------------------------------------
find_package(Vulkan REQUIRED)
if(APPLE)
    find_library(MOLTENVK_LIBRARY MoltenVK PATHS /opt/homebrew/lib /usr/local/lib REQUIRED)
endif()

# -------------------------------------------------
# Sources
# -------------------------------------------------
set(PLATFORM_GUI_SRC
    Acorn/Platform/GUI/ApplicationGui.cpp
    Acorn/Platform/GUI/ImGui/ImGuiBuild.cpp
    Acorn/Platform/GUI/ImGui/ImGuiTheme.cpp
    Acorn/Platform/GUI/Input/Input.cpp
)

add_executable(AcornApp ${PLATFORM_GUI_SRC})

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(AcornApp
    PRIVATE
        ${Vulkan_INCLUDE_DIRS}
        Acorn/vendor
        Acorn/vendor/imgui
        Acorn/vendor/imgui/backends
        Acorn/vendor/yaml-cpp
        Acorn/vendor/spdlog
        Acorn/vendor/glm
)

# -------------------------------------------------
# Link libraries
# -------------------------------------------------
if(APPLE)
    target_link_libraries(AcornApp
        PRIVATE
            GLFW
            yaml-cpp
            ImGui
            Vulkan::Vulkan
            ${MOLTENVK_LIBRARY}
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreGraphics"
            "-framework Metal"
            "-framework QuartzCore"
    )
endif()

# -------------------------------------------------
# macOS specific defines
# -------------------------------------------------
if(APPLE)
    target_compile_definitions(AcornApp PRIVATE VK_USE_PLATFORM_METAL_EXT)
endif()