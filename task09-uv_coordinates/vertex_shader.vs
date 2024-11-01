#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
//ToDo step 6: create a variable to receive texture coordinates

out vec2 tex_coord;
out vec3 out_color;

void main() {
  gl_Position = vec4(a_pos, 1.0);
  out_color = a_color;
  // ToDo step 9: send texture coordinates to fragment shader
}