cmake_minimum_required(VERSION 3.16)

list(APPEND ALL_FILES io)

add_library(io OBJECT io.cpp)
target_include_directories(io PRIVATE ../../../include)
target_include_directories(io PRIVATE ../../../include/operations/io)
set_property(TARGET io PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND OBJECTS $<TARGET_OBJECTS:io>)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)