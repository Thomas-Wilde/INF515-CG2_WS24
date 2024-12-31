# Projects Settings
cmake_minimum_required (VERSION 3.1)
# The main executable
add_executable(Task15-FPSCam
  fps_cam.cc
  shader.cc
  camera.cc
)

set_property(TARGET Task15-FPSCam PROPERTY CXX_STANDARD 17)
target_compile_options(Task15-FPSCam PRIVATE -Wall)
configure_file(fragment_shader.fs fragment_shader.fs COPYONLY)
configure_file(vertex_shader.vs vertex_shader.vs COPYONLY)
configure_file(cubetex.png cubetex.png COPYONLY)

target_link_libraries(
Task15-FPSCam
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)
