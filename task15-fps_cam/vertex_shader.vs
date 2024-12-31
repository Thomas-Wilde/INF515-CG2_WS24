#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 v_tex_coord;

void main() {
  gl_Position = gl_Position = projection * view * model * vec4(a_pos, 1.0);
  v_tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
}
