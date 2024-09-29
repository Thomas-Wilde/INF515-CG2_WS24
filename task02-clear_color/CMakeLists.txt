# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task02-ClearColor
  clear_color.cc
)

set_property(TARGET Task02-ClearColor PROPERTY CXX_STANDARD 17)
target_compile_options(Task02-ClearColor PRIVATE -Wall)

target_link_libraries(
Task02-ClearColor
  PRIVATE glfw
  PRIVATE libglew_static
)
