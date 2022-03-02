cmake_minimum_required(VERSION 3.16)

add_subdirectory(bool)

add_subdirectory(config)

add_subdirectory(core)

add_subdirectory(float)

add_subdirectory(integer)

add_subdirectory(keyset)

add_subdirectory(raw)


set(OBJECTS ${OBJECTS} PARENT_SCOPE)