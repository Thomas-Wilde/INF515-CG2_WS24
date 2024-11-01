#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
//ToDo step 7: create a variable to receive texture coordinates
out vec2 tex_coord;
out vec3 out_color;

uniform float time;

// --- rotate the points around the center
vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

// --- main function
void main() {
  // rotate quad
  float td = time / 2.5;
  vec2 pos = rotate(a_pos.xy, -td);
  pos = pos * (sin(td) + 1.125)/2.0;

  // forward data
  gl_Position = vec4(pos, 0.0, 1.0);
  out_color = a_color;
  // ToDo step 10: send texture coordinates to fragment shader
}
