add_executable(helloworld_cli helloworld.cpp)

target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(helloworld_cli PRIVATE version)

# install instructions
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
