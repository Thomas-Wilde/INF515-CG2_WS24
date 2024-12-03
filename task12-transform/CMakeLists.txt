# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task12-Transformation
  transformation.cc
  shader.cc
)

set_property(TARGET Task12-Transformation PROPERTY CXX_STANDARD 17)
target_compile_options(Task12-Transformation PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)
configure_file(mandala_1000.png mandala_1000.png COPYONLY)

target_link_libraries(
Task12-Transformation
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)
