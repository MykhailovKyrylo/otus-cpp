# ip parser library
add_library(ip_parser STATIC ip.cpp ip_parser.cpp)

target_include_directories(ip_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(ip_parser PRIVATE -Wall -Wextra -pedantic -Werror)

# ip filter client
add_executable(ip_filter_cli ip_filter.cpp)

target_link_libraries(ip_filter_cli PUBLIC ip_parser)

target_compile_options(ip_filter_cli PRIVATE -Wall -Wextra -pedantic -Werror)

# install instructions
install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

# Tests

add_executable(ip_parser_test tests/ip_parser_tests.cpp)

target_link_libraries(ip_parser_test ip_parser gtest gtest_main)

add_test(ip_parser_test ip_parser_test)
