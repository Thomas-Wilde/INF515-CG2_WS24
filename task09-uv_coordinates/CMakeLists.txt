# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task09-UVCoordiantes
  uv_coords.cc
  shader.cc
)

set_property(TARGET Task09-UVCoordiantes PROPERTY CXX_STANDARD 17)
target_compile_options(Task09-UVCoordiantes PRIVATE -Wall)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(texture.jpg texture.jpg COPYONLY)

target_link_libraries(
  Task09-UVCoordiantes
  PRIVATE glfw
  PRIVATE libglew_static
)
