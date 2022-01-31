# Common utils

add_library(version STATIC version/version.cpp)

target_include_directories(version INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/version)

target_compile_definitions(version PRIVATE PROJECT_VERSION_PATCH)

# Tests

add_executable(version_tests tests/version_tests.cpp)

target_link_libraries(version_tests version gtest gtest_main)

add_test(version_tests version_tests)