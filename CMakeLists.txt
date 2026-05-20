cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(shapes)

add_subdirectory(deps/sfml)

add_subdirectory(src)
