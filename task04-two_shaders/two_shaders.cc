#include <array>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ------------------------------------------------------------------------ //
/* forward declarations*/
// clang-format off
struct Scene;
void createShaderProgram(Scene&);
void createTriangleScene(Scene&);
void renderLoop(Scene const&);
// clang-format on

// ------------------------------------------------------------------------ //
/* Scene keeps global app information. An instance of Scene is sent to
   initialziation functions and to the render loop.*/
struct Scene {
  // --- window stuff
  std::string const title = "INF515 - Two Shaders";
  GLFWwindow *window = nullptr;
  int width = 800;  // window width
  int height = 600; // window height
  // --- scene stuff
  GLuint shader_program = -1; // shader program object
  GLuint VAO = -1;            // shader array object
  GLuint VBO = -1;            // vertex buffer object
};

// ------------------------------------------------------------------------ //
/** Initialize the GL framework. */
bool initGLFW() {
  if (!glfwInit()) {
    std::cout << "GLFW initilization failed!" << std::endl;
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL min version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL max version
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  return true;
}

// ------------------------------------------------------------------------ //
bool initGLFWWindow(Scene &s) {
  // --- create window
  s.window = glfwCreateWindow(s.width, s.width, s.title.c_str(), NULL, NULL);
  if (!s.window) {
    std::cout << "Window creation failed!" << std::endl;
    return false;
  }
  glfwGetFramebufferSize(s.window, &s.width, &s.height);
  glfwMakeContextCurrent(s.window);
  return true;
}

// ------------------------------------------------------------------------ //
bool initGLEW() {
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW initialization failed!";
    return false;
  }
  return true;
}

// ------------------------------------------------------------------------ //
int main(void) {
  Scene scene;
  // --- Scene GLFW & GLEW
  if (!initGLFW() || !initGLFWWindow(scene) || !initGLEW()) {
    glfwDestroyWindow(scene.window);
    glfwTerminate();
    return -1;
  };
  glViewport(0, 0, scene.width, scene.height);
  // --- prepare scene
  createShaderProgram(scene);
  createTriangleScene(scene);
  // --- start render loop
  renderLoop(scene);
  //--- clean up before close
  glfwTerminate();
  return 0;
}

// ************************************************************************* //
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ToDo: Add code to draw a triangle image with at least two colors.
// ToDo: Describe your approach in more detail! How does your solution work?
// ToDo: Create a creative image!
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ************************************************************************* //

// ToDo step 1: define vertex shader
// ToDo step 2: define fragment shader
// ------------------------------------------------------------------------ //
void createShaderProgram(Scene &scene) {
  // ToDo step 3: create & compile vertex shader object
  // ToDo step 4: create & compile fragment shader object
  // ToDo step 5: create shader program object
  // ToDo step 6: attach shaders & link shader program
  // ToDo step 7: clean up unnecessary shader stuff
}

// ------------------------------------------------------------------------ //
void createTriangleScene(Scene &scene) {
  // ToDo step 8: create vertex data for triangles
  float vertices[] = {/*ToDo*/};
  // ToDo step 9: create VAO and VBO -- store IDs in scene variable
  // ToDo step 10: bind VAO and VBO
  // ToDo step 11: send vertex data to VBO
  // ToDo step 12: tell OpenGL how to interpret the vertex data
  // ToDo step 13: enable vertex attribute array (index is likely to be 0)
  // ToDo step 14: unbind VBO and VAO (in that order)
}

// ------------------------------------------------------------------------ //
void renderLoop(Scene const &scene) {
  while (!glfwWindowShouldClose(scene.window)) {
    glfwPollEvents();
    glClearColor(0.192f, 0.510f, 0.741f, 1.000f);
    glClear(GL_COLOR_BUFFER_BIT);
    // ToDo step 15: select shader program object (id stored in scene)
    // ToDo step 16: bind VAO from (id stored in scene)
    // ToDo step 17: select draw method
    glfwSwapBuffers(scene.window);
  }
}