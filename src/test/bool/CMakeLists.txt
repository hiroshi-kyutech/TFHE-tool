cmake_minimum_required(VERSION 3.16)

set(SRCS1
alice_bool
verif_bool
)

set(SRCS2
cloud_and
cloud_mux_bool
cloud_not
cloud_or
cloud_xor
)

foreach (FILE IN LISTS SRCS1)
add_executable(${FILE} ${FILE}.cpp)
target_link_libraries(${FILE} tfhe_libex)
target_include_directories(${FILE} PRIVATE ../../include)
endforeach (FILE IN LISTS FILES)

foreach (FILE IN LISTS SRCS2)
add_executable(${FILE} ${FILE}.cpp ../time.cpp)
target_link_libraries(${FILE} tfhe_libex)
target_include_directories(${FILE} PRIVATE ../../include)
endforeach (FILE IN LISTS FILES)