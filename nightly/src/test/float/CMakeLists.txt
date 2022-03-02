cmake_minimum_required(VERSION 3.16)

set(SRCS1
test_float_add
)

foreach (FILE IN LISTS SRCS1)
add_executable(${FILE} ${FILE}.cpp)
target_link_libraries(${FILE} tfhe_libex)
target_include_directories(${FILE} PRIVATE ../../include)
endforeach (FILE IN LISTS FILES)