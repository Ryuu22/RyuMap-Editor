cmake_minimum_required(VERSION 3.5)
project(rmapEditor)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

file(GLOB SOURCES "src/*.cpp")
add_executable(rmapEditor ${SOURCES})

target_link_libraries(rmapEditor raylib)