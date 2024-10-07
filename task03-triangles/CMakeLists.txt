# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task03-Triangles
  triangles.cc
)

set_property(TARGET Task03-Triangles PROPERTY CXX_STANDARD 17)
target_compile_options(Task03-Triangles PRIVATE -Wall)

target_link_libraries(
Task03-Triangles
  PRIVATE glfw
  PRIVATE libglew_static
)
