cmake_minimum_required(VERSION 3.16)

set(SRCS1
alice_array
verif_array
)

set(SRCS2
cloud_bitonic_mergesort
cloud_oem_sort
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