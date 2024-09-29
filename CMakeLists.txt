# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (INF515-Computergrafik_II)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

add_subdirectory(task01-window)
add_subdirectory(task02-clear_color)
