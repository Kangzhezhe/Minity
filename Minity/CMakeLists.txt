cmake_minimum_required(VERSION 3.27.2)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

# -------------- imgui ------------------------------
file(GLOB IMGUI_SRC
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
)

# -------------- Minity ------------------------------
add_definitions(-DMN_PLATFORM_WINDOWS)

file(GLOB_RECURSE MINITY_SRC src/Minity/*.cpp src/Platform/*.cpp)

list(APPEND MINITY_SRC ${IMGUI_SRC})

add_library(Minity SHARED
    ${MINITY_SRC}
)

target_precompile_headers(Minity
    PUBLIC
    src/pch.h
)

target_include_directories(Minity PUBLIC
    src
    src/Minity
    src/Platform
    vendor/imgui
    vendor/imgui/backends
)

target_link_libraries(Minity PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> glfw glad opengl32)