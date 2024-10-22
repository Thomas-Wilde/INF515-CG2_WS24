#pragma once   // avoid multiple definitions

#include <GL/glew.h>   // include glew to get all the required OpenGL headers
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  // the program ID
  unsigned int program_ID;
  // constructor reads and builds the shader
  Shader(const char* vertex_filepath, const char* fragment_filepath);
  void reload(bool verbose = false);
  // use/activate the shader
  void use();
  // utility uniform functions
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;

private:
  void load(bool verbose);

  std::string vertex_filepath{};
  std::string fragment_filepath{};
};