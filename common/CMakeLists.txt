# Common utils

add_library(version STATIC version/version.cpp)

target_include_directories(version INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/version)

target_compile_definitions(version PRIVATE PROJECT_VERSION_PATCH)

# Tests

add_executable(version_tests tests/version_tests.cpp)

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
  message(FATAL_ERROR "Cannot find Google Test Framework!")
endif()

target_link_libraries(version_tests version GTest::GTest GTest::Main)

option(BUILD_TESTING "Whether to build tests" ON)

if (BUILD_TESTING)
  enable_testing()
  add_test(version_tests version_tests)
endif()
