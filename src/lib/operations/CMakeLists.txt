cmake_minimum_required(VERSION 3.16)

add_subdirectory(arithmetic)

add_subdirectory(io)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)
