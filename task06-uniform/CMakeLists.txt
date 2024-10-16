# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task06-Uniform
  uniform.cc
  shader.cc
)

set_property(TARGET Task06-Uniform PROPERTY CXX_STANDARD 17)
target_compile_options(Task06-Uniform PRIVATE -Wall)

target_link_libraries(
Task06-Uniform
  PRIVATE glfw
  PRIVATE libglew_static
)
