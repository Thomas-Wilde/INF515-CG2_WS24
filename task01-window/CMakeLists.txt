# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task01-Window
  window.cc
)

set_property(TARGET Task01-Window PROPERTY CXX_STANDARD 17)
target_compile_options(Task01-Window PRIVATE -Wall)

target_link_libraries(
Task01-Window
  PRIVATE glfw
  PRIVATE libglew_static
)
