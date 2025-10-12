cmake_minimum_required(VERSION 3.30)

project(MY_PROJECT1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    src/main.cpp
    src/core/Reader.cpp
    src/core/NHFS.cpp
    src/utils/app_conf.cpp
)

set_target_properties(main PROPERTIES OUTPUT_NAME "fioc")

target_include_directories(main PRIVATE
    "include"
    "include/core"
    "include/utils"
)

target_link_options(main PRIVATE
    -static
    -static-libgcc
    -static-libstdc++
)
