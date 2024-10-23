#version 330 core
out vec4      frag_color;
uniform float time;

const vec4 clr0 = vec4(228.0 / 255.0, 26.0 / 255.0, 28.0 / 255.0, 1.0);
const vec4 clr1 = vec4(55.0 / 255.0, 126.0 / 255.0, 184.0 / 255.0, 1.0);
const vec4 clr2 = vec4(77.0 / 255.0, 175.0 / 255.0, 74.0 / 255.0, 1.0);
const vec4 clr3 = vec4(152.0 / 255.0, 78.0 / 255.0, 163.0 / 255.0, 1.0);
const vec4 clr4 = vec4(255.0 / 255.0, 127.0 / 255.0, 0.0 / 255.0, 1.0);

// ---
void
main() {
  frag_color = vec4(1);
}
