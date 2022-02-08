# custom allocator library
add_library(custom_allocator_lib INTERFACE)

target_include_directories(custom_allocator_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# example executable

add_executable(custom_allocator_example example.cpp)

target_link_libraries(custom_allocator_example PRIVATE custom_allocator_lib)

target_compile_options(custom_allocator_example PRIVATE -Wall -Wextra -pedantic -Werror)

# Tests

add_executable(custom_allocator_tests tests/custom_allocator_tests.cpp)

target_link_libraries(custom_allocator_tests custom_allocator_lib gtest gtest_main)

add_test(custom_allocator_tests custom_allocator_tests)
