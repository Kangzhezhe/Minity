cmake_minimum_required(VERSION 3.27.2)


add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)


# -------------- Minity ------------------------------
add_definitions(-DMN_PLATFORM_WINDOWS)

file(GLOB_RECURSE MINITY_SRC src/Minity/*.cpp)

add_library(Minity SHARED
    ${MINITY_SRC}
)

target_precompile_headers(Minity
    PUBLIC
        src/pch.h
)

target_include_directories(Minity PUBLIC
    src
)

target_link_libraries(Minity PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> glfw glad)