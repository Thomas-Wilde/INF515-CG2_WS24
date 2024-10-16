#include "shader.hh"

// ------------------------------------------------------------------------
Shader::Shader(const char* vertex_filepath, const char* fragment_filepath)
  : vertex_filepath(vertex_filepath)
  , fragment_filepath(fragment_filepath) {
  load();
}

// ------------------------------------------------------------------------
void
Shader::reload() {
  glDeleteProgram(program_ID);
  load();
}

// ------------------------------------------------------------------------
void
Shader::use() {
  glUseProgram(program_ID);
}

// ************************************************************************* //
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ToDo: Add code for the shader class below.
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ************************************************************************* //

// ------------------------------------------------------------------------
void
Shader::load() {
  // ToDo step 1: read the source code from the given filepaths.
  // ToDo step 2: create and compile the shaders
  // ToDo step 3: create and link the shader program
  // ToDo step 4: clean up unnecessary stuff

  // ToDo: always check if everyting went well
  // ToDo: handle excepetions if possible
  // ToDo: print out information when failures occured
}

// ------------------------------------------------------------------------
void
Shader::setBool(const std::string& name, bool value) const {
  // ToDo: update the correct unfiform
}
// ------------------------------------------------------------------------
void
Shader::setInt(const std::string& name, int value) const {
  // ToDo: update the correct unfiform
}
// ------------------------------------------------------------------------
void
Shader::setFloat(const std::string& name, float value) const {
  // ToDo: update the correct unfiform
}