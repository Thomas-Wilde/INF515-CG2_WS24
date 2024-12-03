#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;

uniform int render_mode;
uniform mat4 transform;

out vec2 v_tex_coord;

void main() {
  // ToDo step 2: change shader to perform transformation
  gl_Position = vec4(a_pos, 1.0);
  v_tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
}