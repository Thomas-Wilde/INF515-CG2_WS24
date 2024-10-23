# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task08-Animation
  animation.cc
  shader.cc
)

set_property(TARGET Task08-Animation PROPERTY CXX_STANDARD 17)
target_compile_options(Task08-Animation PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)

target_link_libraries(
Task08-Animation
  PRIVATE glfw
  PRIVATE libglew_static
)
