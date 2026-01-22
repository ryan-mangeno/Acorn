project(AcornApp LANGUAGES CXX)

file(GLOB_RECURSE SRC
    Source/*.h
    Source/*.cpp
    Platform/GUI/*.h
    Platform/GUI/*.cpp
)

add_library(AcornApp STATIC ${SRC})

target_compile_features(AcornApp PUBLIC cxx_std_20)

target_include_directories(AcornApp
    PUBLIC
        Source
        Platform/GUI
        vendor/imgui
        vendor/glfw/include
        vendor/stb_image
        ${IncludeDir_VulkanSDK}
        ${IncludeDir_glm}
        ${IncludeDir_spdlog}
)

target_link_libraries(AcornApp
    PUBLIC
        ImGui
        GLFW
        Vulkan::Vulkan
)

if(WIN32)
    target_compile_definitions(AcornApp PUBLIC WL_PLATFORM_WINDOWS)
endif()

target_compile_definitions(AcornApp PRIVATE
    $<$<CONFIG:Debug>:WL_DEBUG>
    $<$<CONFIG:Release>:WL_RELEASE>
    $<$<CONFIG:Dist>:WL_DIST>
)
