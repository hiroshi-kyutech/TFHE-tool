cmake_minimum_required(VERSION 3.16)

list(APPEND ALL_FILES config)

add_library(config OBJECT config.cpp)
target_include_directories(config PRIVATE ../../../include)
target_include_directories(config PRIVATE ../../../include/type/config)
set_property(TARGET config PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND OBJECTS $<TARGET_OBJECTS:config>)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)