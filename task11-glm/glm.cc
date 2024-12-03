#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "load_stb.hh"
#include "shader.hh"

// ------------------------------------------------------------------------ //
/* Settings keeps global app information. */
struct Settings {
  std::string const title         = "INF515-GLM";
  int               window_width  = 800;
  int               window_height = 800;
  GLFWwindow*       window        = nullptr;
  int               buffer_width  = -1;
  int               buffer_height = -1;
  // --- settings for the scene and interaction
  int  render_mode = 0;
  bool press_r     = false;
  bool press_s     = false;
  bool press_m     = false;
  int  shot_count  = 0;
};

// ------------------------------------------------------------------------ //
/* A simple struct to define colors in RGB mode in [0,255] or [0,1] interval.*/
struct Color {
  Color(int r, int g, int b)
    : r(r / 255.f)
    , g(g / 255.f)
    , b(b / 255.f) {}

  Color(float r, float g, float b)
    : r(r)
    , g(g)
    , b(b){};

  float r = 0;
  float g = 0;
  float b = 0;
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
void
resizeWindow(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
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
loadTexture(std::string const& filename) {
  // --- load the image from file
  unsigned int texture = -1;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  // set texture filtering parameters
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and flip image, create texture and generate mipmaps
  int width       = -1;
  int height      = -1;
  int nr_channels = -1;
  // flip loaded texture's on the y-axis.
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data =
    stbi_load(filename.c_str(), &width, &height, &nr_channels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    std::cout << "Loaded texture: " << filename << std::endl;
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // --- enable blending for alpha channel
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// ------------------------------------------------------------------------ //
void
createScene(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO) {
  Color cc{ 42, 42, 42 };   // clear color
  glClearColor(cc.r, cc.g, cc.b, 1.0f);

  // --- set up vertex data (and buffers) and configure vertex attributes
  // clang-format off
  float vertices[] = {
    // positions         // texture coordinates
     0.75f,  0.75f, 0.0f, +1.0f,  +1.0f,
     0.75f, -0.75f, 0.0f, +1.0f,  -0.0f,
    -0.75f, -0.75f, 0.0f, -0.0f,  -0.0f,
    -0.75f,  0.75f, 0.0f, -0.0f,  +1.0f
  };

  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };
  // clang-format on

  loadTexture("hextex_arrow.png");

  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  glGenBuffers(1, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // --- position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  // --- texture coordinate attribute
  glVertexAttribPointer(
    1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// ------------------------------------------------------------------------ //
void
takeScreenshot(Settings& setup) {
  int width, height;
  glfwGetWindowSize(setup.window, &width, &height);
  GLubyte* screen = new GLubyte[width * height * 4];
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, screen);
  // --- flip the image upside down
  GLubyte* screen2 = new GLubyte[width * height * 4];
  for (int x = 0; x < width; ++x)
    for (int y = 0; y < height; ++y)
      for (int z = 0; z < 4; ++z) {
        screen2[z + x * 4 + (height - y - 1) * width * 4] =
          screen[z + x * 4 + y * width * 4];
      }
  // --- generate filename
  std::string filename = "screenshot";
  if (setup.shot_count < 100) {
    filename.append("0");
  }
  if (setup.shot_count < 10) {
    filename.append("0");
  }
  filename += std::to_string(setup.shot_count++) + std::string(".png");
  // --- save the file
  stbi_write_png(filename.c_str(), width, height, 4, screen2, 0);
  std::cout << "saved image to: " << filename << std::endl;
  delete[] screen;
  delete[] screen2;
}

// ------------------------------------------------------------------------ //
void
handleKeyboardEvents(Settings& setup, Shader& shader) {
  // --- ESC -> close window ---//
  if (glfwGetKey(setup.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    return glfwSetWindowShouldClose(setup.window, true);
  }

  // ==========================================================================
  // --- M -> switch rendermode ---//
  if (glfwGetKey(setup.window, GLFW_KEY_M) == GLFW_PRESS && !setup.press_m) {
    setup.press_m = true;
    setup.render_mode += 1;
    shader.setInt("render_mode", setup.render_mode);
    takeScreenshot(setup);
    return;
  }
  if (glfwGetKey(setup.window, GLFW_KEY_M) == GLFW_RELEASE && setup.press_m) {
    setup.press_m = false;
    return;
  }

  // ==========================================================================
  // --- R -> reload shader ---//
  if ((glfwGetKey(setup.window, GLFW_KEY_R) == GLFW_PRESS) && !setup.press_r) {
    setup.press_r = true;
    shader.reload();
    setup.render_mode = 0;
    shader.setInt("render_mode", 0);
    std::cout << "reload shader" << std::endl;
    return;
  }
  if ((glfwGetKey(setup.window, GLFW_KEY_R) == GLFW_RELEASE) && setup.press_r) {
    setup.press_r = false;
    return;
  }

  // ==========================================================================
  // --- S -> take screenshot ---//
  if (glfwGetKey(setup.window, GLFW_KEY_S) == GLFW_PRESS && !setup.press_s) {
    setup.press_s = true;
    takeScreenshot(setup);
    return;
  }
  if (glfwGetKey(setup.window, GLFW_KEY_S) == GLFW_RELEASE && setup.press_s) {
    setup.press_s = false;
    return;
  }
}

// ------------------------------------------------------------------------ //
void
updateTransformation(int program_ID) {
  // ToDo - step 1: enter your code for transformation here
  // Transformation should do the following things:
  // - rotate around z-axis by 90 degree
  // - move the object along y-axis for 0.5 units
  // - scale the object with the vector (0.25, 0.25, 1.0)
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// ------------------------------------------------------------------------ //
void
renderLoop(Settings& setup) {
  Shader shader = Shader{ "vertex_shader.vs", "fragment_shader.fs" };

  unsigned int VAO = 0;
  unsigned int VBO = 0;
  unsigned int EBO = 0;
  createScene(&VAO, &VBO, &EBO);

  // --- render loop
  while (!glfwWindowShouldClose(setup.window)) {
    // --- poll for and process events like mouse input --- //
    glfwPollEvents();
    handleKeyboardEvents(setup, shader);

    // --- clear the window --- //
    shader.use();
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    updateTransformation(shader.program_ID);
    // --- swap front and back buffers (we use double buffering) ---//
    glfwSwapBuffers(setup.window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shader.program_ID);
}

// ------------------------------------------------------------------------ //
int
main(void) {
  std::cout << "Computer Graphics Tutorial" << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "Press M   to change render mode." << std::endl;
  std::cout << "Press R   to reload the shader." << std::endl;
  std::cout << "Press S   to take a screenshot." << std::endl;
  std::cout << "Press ESC to exit the program." << std::endl;
  std::cout << "==========================" << std::endl;

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
  glfwSetFramebufferSizeCallback(settings.window, resizeWindow);

  // --- render
  renderLoop(settings);
  //--- clean up before close
  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}