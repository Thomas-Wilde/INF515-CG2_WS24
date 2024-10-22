# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task06-Uniform
  uniform.cc
  shader.cc
)

set_property(TARGET Task06-Uniform PROPERTY CXX_STANDARD 17)
target_compile_options(Task06-Uniform PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)

target_link_libraries(
Task06-Uniform
  PRIVATE glfw
  PRIVATE libglew_static
)
