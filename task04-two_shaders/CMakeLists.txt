# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task04-TwoShaders
  two_shaders.cc
)

set_property(TARGET Task04-TwoShaders PROPERTY CXX_STANDARD 17)
target_compile_options(Task04-TwoShaders PRIVATE -Wall)

target_link_libraries(
Task04-TwoShaders
  PRIVATE glfw
  PRIVATE libglew_static
)
