cmake_minimum_required(VERSION 3.16)

set(SRCS1
alice_integer
verif_integer
verif_bool_integer
test_error_check
)

set(SRCS2
cloud_abs
cloud_add
cloud_div
cloud_equal_to
cloud_less_than
cloud_minus
cloud_mod
cloud_mul
cloud_mux_integer
cloud_sign
cloud_sub
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