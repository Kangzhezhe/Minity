cmake_minimum_required(VERSION 3.27.2)

project(SandBox)

add_executable(SandBox src/SandBoxApp.cpp)

target_link_libraries(SandBox
    Minity
)