# vector graphics editor
add_library(vector_graphics_editor STATIC
        default_types.cpp
        document.cpp
        object_storage.cpp
        visualizer.cpp)

target_compile_options(vector_graphics_editor PRIVATE -Wall -Wextra -pedantic -Werror)

# vector graphics editor example
add_executable(vector_graphics_editor_example main.cpp)

target_link_libraries(vector_graphics_editor_example PRIVATE vector_graphics_editor)

# install instructions
install(TARGETS vector_graphics_editor_example RUNTIME DESTINATION bin)
