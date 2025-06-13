cmake_minimum_required(VERSION 3.27.2)

project(SandBox)

file(GLOB_RECURSE SAND_BOX_SRC src/*.cpp)

add_executable(SandBox ${SAND_BOX_SRC})

target_link_libraries(SandBox
    Minity
)