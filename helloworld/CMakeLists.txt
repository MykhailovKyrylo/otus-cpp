add_executable(helloworld_cli helloworld.cpp)

target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(helloworld_cli PRIVATE version)

# install instructions
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

# DEB PACK
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
