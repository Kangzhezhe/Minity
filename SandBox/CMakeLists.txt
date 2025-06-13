cmake_minimum_required(VERSION 3.27.2)

project(SandBox)


add_executable(SandBox src/SandBoxApp.cpp)
target_include_directories(SandBox PRIVATE
    ${CMAKE_SOURCE_DIR}/Minity/src
)

target_link_libraries(SandBox
    Minity
)