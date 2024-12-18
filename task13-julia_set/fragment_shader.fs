#version 330 core
out vec4 frag_color;

uniform float time;
uniform int   render_mode;
uniform int   window_height;
uniform int   window_width;

// ------------------------------------------- //
void
main() {
  frag_color = vec4(1.0, 0.5, 0.0, 1.0);
}