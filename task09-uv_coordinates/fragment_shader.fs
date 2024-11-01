#version 330 core
out vec4    frag_color;
in vec3     out_color;
// ToDo step 10: receive texture coordiantes from vertex shader
uniform int render_mode;
// ToDo step 12: provide a sampler / texture unit to read the texture

void
main() {
  // --- read texture color
  // ToDo step 13: replace code to read color from texture
  vec4 tex_col = vec4(1.0);

  // --- set color based on mode
  const int modes = 2;
  if (render_mode % modes == 0) {
    frag_color = vec4(out_color, 1.0);
  }
  if (render_mode % modes == 1) {
    frag_color = tex_col;
  }
}