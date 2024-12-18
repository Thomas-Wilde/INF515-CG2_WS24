#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;
// --- ToDo: provide variables to get model matrix
// --- ToDo: provide variables to get view matrix
// --- ToDo: provide variables to get projection matrix

out vec2 v_tex_coord;

void main() {
  // --- ToDo: transform position
  gl_Position = a_pos;  // <--- perform transformation onto this position
  v_tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
}
