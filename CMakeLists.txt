cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(otus-cpp VERSION ${PROJECT_VERSION})

option(BUILD_TESTING "Whether to build tests" ON)

if (BUILD_TESTING)
    enable_testing()
endif ()

add_subdirectory(3d-party)

add_subdirectory(common)

add_subdirectory(helloworld)

add_subdirectory(ip-filter)

add_subdirectory(custom-allocator)

add_subdirectory(ip-printer)

# DEB PACK
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
