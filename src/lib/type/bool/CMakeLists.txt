cmake_minimum_required(VERSION 3.16)

list(APPEND ALL_FILES bool)

add_library(bool OBJECT bool.cpp)
target_include_directories(bool PRIVATE ../../../include)
target_include_directories(bool PRIVATE ../../../include/type/bool)
set_property(TARGET bool PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND OBJECTS $<TARGET_OBJECTS:bool>)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)