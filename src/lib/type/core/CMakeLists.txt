cmake_minimum_required(VERSION 3.16)

set(SRCS
bool_core
integer_core
)

foreach (FILE IN LISTS SRCS)
add_library(${FILE} OBJECT ${FILE}.cpp)
target_include_directories(${FILE} PRIVATE ../../../include)
target_include_directories(${FILE} PRIVATE ../../../include/type/core)
set_property(TARGET ${FILE} PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND OBJECTS $<TARGET_OBJECTS:${FILE}>)
endforeach (FILE IN LISTS FILES)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)
