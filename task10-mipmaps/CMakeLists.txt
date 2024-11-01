# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task10-Mipmaps
  mipmaps.cc
  shader.cc
)

set_property(TARGET Task10-Mipmaps PROPERTY CXX_STANDARD 17)
target_compile_options(Task10-Mipmaps PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)
configure_file(map01.jpg map01.jpg COPYONLY)
configure_file(map02.jpg map02.jpg COPYONLY)
configure_file(map03.jpg map03.jpg COPYONLY)
configure_file(map04.jpg map04.jpg COPYONLY)
configure_file(map05.jpg map05.jpg COPYONLY)
configure_file(map06.jpg map06.jpg COPYONLY)

target_link_libraries(
Task10-Mipmaps
  PRIVATE glfw
  PRIVATE libglew_static
)
