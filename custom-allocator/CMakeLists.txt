# custom allocator library
add_library(custom_allocator_lib INTERFACE)

target_include_directories(custom_allocator_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# custom list library

add_library(custom_list_lib INTERFACE)

target_include_directories(custom_list_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# example executable

add_executable(custom_allocator_example example.cpp)

target_link_libraries(custom_allocator_example PRIVATE custom_allocator_lib)

target_compile_options(custom_allocator_example PRIVATE -Wall -Wextra -pedantic -Werror)

# install instructions
install(TARGETS custom_allocator_example RUNTIME DESTINATION bin)

# Tests

# custom allocator tests
add_executable(custom_allocator_tests tests/custom_allocator_tests.cpp)

target_link_libraries(custom_allocator_tests custom_allocator_lib gtest gtest_main)

add_test(custom_allocator_tests custom_allocator_tests)

# custom list tests
add_executable(custom_list_tests tests/custom_list_tests.cpp)

target_link_libraries(custom_list_tests custom_list_lib gtest gtest_main)

add_test(custom_allocator_tests custom_allocator_tests)
