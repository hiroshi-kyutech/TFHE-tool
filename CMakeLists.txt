cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "tfhe_libex")

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

add_subdirectory(src)
