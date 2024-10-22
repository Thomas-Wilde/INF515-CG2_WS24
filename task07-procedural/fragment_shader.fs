#version 330 core
out vec4      frag_color;
uniform float time;
uniform int render_mode;

const vec4 clr0 = vec4(228.0/255.0,  26.0/255.0,  28.0/255.0,1.0);
const vec4 clr1 = vec4( 55.0/255.0, 126.0/255.0, 184.0/255.0,1.0);
const vec4 clr2 = vec4( 77.0/255.0, 175.0/255.0,  74.0/255.0,1.0);
const vec4 clr3 = vec4(152.0/255.0,  78.0/255.0, 163.0/255.0,1.0);
const vec4 clr4 = vec4(255.0/255.0, 127.0/255.0,   0.0/255.0,1.0);

// ---
void renderCircle() {
  frag_color = clr1;
}

// ---
void renderDiamond() {
  frag_color = clr2;
}

// ---
void renderCheckerboard() {
  frag_color = clr3;
}

// ---
void renderPattern1() {
  frag_color = clr4;
}

// ---
void renderPattern2() {
  frag_color = clr0;
}

void
main() {
  int mode_count = 5;
  if (render_mode % mode_count == 0)
    renderCircle();
  if (render_mode % mode_count == 1)
    renderDiamond();
  if (render_mode % mode_count == 2)
    renderCheckerboard();
  if (render_mode % mode_count == 3)
    renderPattern1();
  if (render_mode % mode_count == 4)
    renderPattern2();
}
