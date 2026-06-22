cmake_minimum_required(VERSION 3.25)

project(SLangDemo LANGUAGES CXX)

add_executable(SLangDemo
    Source/Main.cpp
    Source/SDR.cpp
)

target_compile_features(SLangDemo PRIVATE cxx_std_20)
target_include_directories(SLangDemo PRIVATE Source)

set_target_properties(SLangDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compiled-out/bin"
)
