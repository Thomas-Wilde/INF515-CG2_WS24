#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hh"

// ------------------------------------------------------------------------ //
/* Settings keeps global app information. */
struct Settings {
  std::string const title         = "INF515 - Uniforms";
  int               window_width  = 800;
  int               window_height = 600;
  GLFWwindow*       window        = nullptr;
  int               buffer_width  = -1;
  int               buffer_height = -1;
};

// ------------------------------------------------------------------------ //
/** Initialize the GL framework. */
bool
initGLFW() {
  if (!glfwInit()) {
    std::cout << "GLFW initilization failed!";
    glfwTerminate();
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);   // OpenGL min version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   // OpenGL max version
  // core profile -> do not allow backward compatability
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // core profile -> do allow foward compatability
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  return true;
}

// ------------------------------------------------------------------------ //
bool
initGLFWWindow(Settings& s) {
  // --- create window
  s.window = glfwCreateWindow(
    s.window_width, s.window_height, s.title.c_str(), NULL, NULL);
  if (!s.window) {
    std::cout << "Window creation failed!" << std::endl;
    return false;
  }
  // --- read frame buffer size
  glfwGetFramebufferSize(s.window, &s.buffer_width, &s.buffer_height);
  // --- set context for GLFW to use
  glfwMakeContextCurrent(s.window);
  std::cout << "window created" << std::endl;
  return true;
}

// ------------------------------------------------------------------------ //
bool
initGLEW() {
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW initialization failed!" << std::endl;
    return false;
  }
  std::cout << "GLEW initialized" << std::endl;
  return true;
}

// ------------------------------------------------------------------------ //
void
renderLoop(Settings& s) {
  Shader our_shader = Shader{ "vertex_shader.vs", "fragment_shader.fs" };

  struct Color {
    Color(int ri, int gi, int bi)
      : r{ ri / 255.f }
      , g{ gi / 255.f }
      , b{ bi / 255.f } {};
    float r = 0;
    float g = 0;
    float b = 0;
  };
  Color c0{ 27, 158, 119 };
  Color c1{ 55, 126, 184 };
  Color c2{ 255, 127, 0 };
  Color c3{ 152, 78, 163 };

  // --- set up vertex data (and buffers) and configure vertex attributes
  // clang-format off
  float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  c1.r, c1.g, c1.b,  // bottom right
    -0.5f, -0.5f, 0.0f,  c2.r, c2.g, c2.b,  // bottom left
     0.0f,  0.5f, 0.0f,  c3.r, c3.g, c3.b   // top
  };
  // clang-format on

  unsigned int VBO = 0;
  unsigned int VAO = 0;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // --- render loop
  while (!glfwWindowShouldClose(s.window)) {
    //--- poll for and process events like mouse input
    glfwPollEvents();

    // ToDo: Close the window, when ESC is pressed.
    // ToDo: Reload the shader, when key 1 is pressed.
    // ToDo: Switch color mode, when key 2 is pressed.
    // ToDo: Scale the triangle over time.

    // --- clear the window
    glClearColor(c0.r, c0.g, c0.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    our_shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // --- swap front and back buffers (we use double buffering) ---//
    glfwSwapBuffers(s.window);
  }
}

// ------------------------------------------------------------------------ //
int
main(void) {
  Settings settings;
  // --- setup GLFW
  if (!initGLFW() || !initGLFWWindow(settings)) {
    glfwTerminate();
    return -1;
  };

  // --- setup GLEW
  if (!initGLEW()) {
    glfwDestroyWindow(settings.window);
    glfwTerminate();
    return -1;
  }

  // --- setup viewport size
  glViewport(0, 0, settings.buffer_width, settings.buffer_height);
  // --- render
  renderLoop(settings);
  //--- clean up before close
  glfwTerminate();
  return 0;
}