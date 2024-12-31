#include "camera.hh"

// ToDo: implement this class

glm::mat4
Camera::getViewMatrix() const {
  glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.5, 5.0),    // Camera position
                               glm::vec3(0.0, 0.0, 0.0),    // Look-at point
                               glm::vec3(0.0, 1.0, 0.0));   // Up vector
  return view;
}
