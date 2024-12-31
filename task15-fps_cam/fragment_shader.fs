#version 330 core
out vec4 frag_color;
in vec2  v_tex_coord;
// texture sampler
uniform sampler2D texture1;

void
main() {
  vec4 tex_col = texture(texture1, v_tex_coord);
  frag_color   = tex_col;
}