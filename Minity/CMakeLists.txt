cmake_minimum_required(VERSION 3.27.2)


add_subdirectory(vendor/spdlog)


# -------------- Minity ------------------------------
file(GLOB_RECURSE MINITY_SRC src/Minity/*.cpp)

add_library(Minity SHARED
    ${MINITY_SRC}
)

target_include_directories(Minity PUBLIC
    src
)

target_link_libraries(Minity PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)