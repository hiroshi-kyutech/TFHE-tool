cmake_minimum_required(VERSION 3.16)

set(OBJECTS)

add_subdirectory(operations)

add_subdirectory(type)

find_package(Threads REQUIRED)

add_library(tfhe_libex SHARED ${OBJECTS})

target_link_libraries(tfhe_libex tfhe-spqlios-fma Threads::Threads)