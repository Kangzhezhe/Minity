cmake_minimum_required(VERSION 3.27.2)


add_subdirectory(vendor/spdlog)


# -------------- Minity ------------------------------
add_library(Minity SHARED
    src/Minity/Application.cpp
    src/Minity/example.cpp
)

target_include_directories(Minity PUBLIC
    src
)

target_link_libraries(Minity PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)