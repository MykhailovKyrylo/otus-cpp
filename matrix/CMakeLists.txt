# matrix library
find_package(Boost REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()

add_library(matrix STATIC matrix.cpp)

target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})

target_link_libraries(matrix PUBLIC ${Boost_LIBRARIES})

# matrix client

add_executable(matrix_cli matrix_cli.cpp)

target_link_libraries(matrix_cli PRIVATE matrix)

target_compile_options(matrix_cli PRIVATE -Wall -Wextra -pedantic -Werror)

# install instructions
install(TARGETS matrix_cli RUNTIME DESTINATION bin)

# Tests

add_executable(matrix_test tests/matrix_tests.cpp)

target_link_libraries(matrix_test matrix gtest gtest_main)

add_test(matrix_test matrix_test)
