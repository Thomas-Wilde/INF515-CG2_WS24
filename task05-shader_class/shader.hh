#pragma once   // avoid multiple definitions

#include <GL/glew.h>   // include glew to get all the required OpenGL headers
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  // the shader program ID / object, we keep this public for access
  unsigned int program_ID;

  // Constructor saves the filepaths for the shaders.
  Shader(const char* vertex_filepath, const char* fragment_filepath);

  // Read the file content and create the shader program.
  void load();

  // Reload the shader program.
  void reload();

  // Use/activate the shader program.
  void use();

  // utility uniform functions
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;

private:
  std::string vertex_filepath{};
  std::string fragment_filepath{};
};