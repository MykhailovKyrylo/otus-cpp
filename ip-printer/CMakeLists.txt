# ip printer library
add_library(ip_printer INTERFACE)

target_include_directories(ip_printer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# ip printer client

add_executable(ip_printer_cli ip_printer_cli.cpp)

target_link_libraries(ip_printer_cli PRIVATE ip_printer)

target_compile_options(ip_printer_cli PRIVATE -Wall -Wextra -pedantic -Werror)

# install instructions
install(TARGETS ip_printer_cli RUNTIME DESTINATION bin)

# Tests
#
#add_executable(ip_printer_test tests/ip_printer_tests.cpp)
#
#target_link_libraries(ip_printer_test ip_printer gtest gtest_main)
#
#add_test(ip_printer_test ip_printer_test)
