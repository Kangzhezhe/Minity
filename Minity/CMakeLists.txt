cmake_minimum_required(VERSION 3.27.2)

add_library(Minity SHARED
    src/Minity/Application.cpp
)

target_include_directories(Minity PUBLIC
    src/Minity
)