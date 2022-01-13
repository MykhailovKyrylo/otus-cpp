# Common utils

add_library(version STATIC version/version.cpp)

target_include_directories(version INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/version)

target_compile_definitions(version PRIVATE PROJECT_VERSION_PATCH)