# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task11-GLM
  glm.cc
  shader.cc
)

set_property(TARGET Task11-GLM PROPERTY CXX_STANDARD 17)
target_compile_options(Task11-GLM PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)
configure_file(hextex_arrow.png hextex_arrow.png COPYONLY)

target_link_libraries(
Task11-GLM
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)
