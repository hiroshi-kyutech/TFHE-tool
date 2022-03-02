cmake_minimum_required(VERSION 3.16)

add_library(keyset OBJECT keyset.cpp)
target_include_directories(keyset PRIVATE ../../../include)
target_include_directories(keyset PRIVATE ../../../include/type/keyset)
set_property(TARGET keyset PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND OBJECTS $<TARGET_OBJECTS:keyset>)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)
