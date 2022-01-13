# Common utils

configure_file(version/version.h.in version/version.h)

add_library(version INTERFACE)
target_include_directories(version INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/version)
