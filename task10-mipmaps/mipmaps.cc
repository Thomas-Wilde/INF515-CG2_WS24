#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "load_stb.hh"
#include "shader.hh"

// ------------------------------------------------------------------------ //
/* Settings keeps global app information. */
struct Settings {
  std::string const title         = "INF515-Mipmaps";
  int               window_width  = 800;
  int               window_height = 800;
  // view
  GLFWwindow* window = nullptr;
  // --- settings for the scene and interaction
  int  render_mode = false;
  bool press_m     = false;
  bool press_r     = false;
  bool press_s     = false;
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
/** Loads a bunch of textures, creates a mipmap texture  and saves the texture
 * id in the provided parameter `id`*/
void
loadMipmapTexture(std::vector<std::string> const& filenames, unsigned int* id) {
  return;
  // ToDo step 1: create and bind a texture object -> save it in `id`
  // ToDo step 2: set texture wrapping parameters
  // ToDo step 3: set texture filtering parameters
  // ToDo step 4: set levels of mipmap pyramid
  // ToDo step 5: load all the texture data, according to the file list and
  //              remind texture width and height for each file
  // ToDo step 6: send texture information to OpenGL with according mipmap
  //              level, width and height for each loaded data set

  // ToDo: provide information on the console if errors occure
  // ToDo: free memory / image data after OpenGL got its information
}

// ------------------------------------------------------------------------ //
void
createScene(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO) {
  Color cc{ 27, 158, 119 };   // clear color
  glClearColor(cc.r, cc.g, cc.b, 1.0f);

  // --- set up vertex data (and buffers) and configure vertex attributes
  // clang-format off
  float vertices[] = {
    // positions         //colors           // tex coords
    -0.75f, -0.75f, 0.0f,  1.0f, 0.0f, 0.0f,  0.00f,  0.00f,
     0.75f, -0.75f, 0.0f,  0.0f, 1.0f, 0.0f,  1.00f,  0.00f,
     0.75f,  0.75f, 0.0f,  0.0f, 0.0f, 1.0f,  1.00f,  1.00f,
    -0.75f,  0.75f, 0.0f,  1.0f, 1.0f, 0.0f,  0.00f,  1.00f,
  };

  unsigned int indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
  };
  // clang-format on
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
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
  glEnableVertexAttribArray(0);

  // --- color attribute
  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // --- texture coordinate attribute
  // ToDo step 8: use glVertexAttribPointer(...) to provide information about
  //              texture data
  // ToDo step 9: enable vertex attributes based on location in shader

  glBindBuffer(GL_ARRAY_BUFFER, 1);
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
  // ==========================================================================
  // --- ESC -> close window ---//
  if (glfwGetKey(setup.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    return glfwSetWindowShouldClose(setup.window, true);
  }

  // ==========================================================================
  // --- R -> reload shader ---//
  if ((glfwGetKey(setup.window, GLFW_KEY_R) == GLFW_PRESS) && !setup.press_r) {
    setup.press_r     = true;
    setup.render_mode = 0;
    shader.reload();
    shader.setInt("render_mode", 0);
    std::cout << "reload shader" << std::endl;
    return;
  }
  if ((glfwGetKey(setup.window, GLFW_KEY_R) == GLFW_RELEASE) && setup.press_r) {
    setup.press_r = false;
    return;
  }

  // ==========================================================================
  // --- M -> switch render mode ---//
  if ((glfwGetKey(setup.window, GLFW_KEY_M) == GLFW_PRESS) && !setup.press_m) {
    setup.press_m = true;
    setup.render_mode++;
    shader.setInt("render_mode", setup.render_mode);
    return;
  }
  if ((glfwGetKey(setup.window, GLFW_KEY_M) == GLFW_RELEASE) && setup.press_m) {
    setup.press_m = false;
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
renderLoop(Settings& setup) {
  Shader shader = Shader{ "vertex_shader.vs", "fragment_shader.fs" };
  shader.setInt("render_mode", 0);

  unsigned int VAO = 0;
  unsigned int VBO = 0;
  unsigned int EBO = 0;
  createScene(&VAO, &VBO, &EBO);

  // --- load texture
  unsigned int texture_id = 0;
  loadMipmapTexture({ "map01.jpg",
                      "map02.jpg",
                      "map03.jpg",
                      "map04.jpg",
                      "map05.jpg",
                      "map06.jpg" },
                    &texture_id);

  // --- render loop
  while (!glfwWindowShouldClose(setup.window)) {
    // --- poll for and process events like mouse input --- //
    glfwPollEvents();
    handleKeyboardEvents(setup, shader);
    double time = glfwGetTime();
    shader.setFloat("time", time);

    // --- clear the window --- //
    shader.use();
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
  std::cout << "Press M   to switch render mode." << std::endl;
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
  int buffer_width  = 0;
  int buffer_height = 0;
  glfwGetFramebufferSize(settings.window, &buffer_width, &buffer_height);
  glViewport(0, 0, buffer_width, buffer_height);
  glfwSetFramebufferSizeCallback(settings.window, resizeWindow);

  // --- render
  renderLoop(settings);

  //--- clean up before close
  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}