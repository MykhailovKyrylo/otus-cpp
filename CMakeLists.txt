cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(otus-cpp VERSION ${PROJECT_VERSION})

add_subdirectory(common)

add_subdirectory(helloworld)
