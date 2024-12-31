#include "shader.hh"

// ------------------------------------------------------------------------
Shader::Shader(const char* vertex_filepath, const char* fragment_filepath)
  : vertex_filepath(vertex_filepath)
  , fragment_filepath(fragment_filepath) {
  load(true);
}

// ------------------------------------------------------------------------
void
Shader::load(bool verbose) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string   vertex_code;
  std::string   fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;
  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // open files
    v_shader_file.open(vertex_filepath);
    f_shader_file.open(fragment_filepath);
    std::stringstream v_shader_stream;
    std::stringstream f_shader_stream;
    // read file’s buffer contents into streams
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code   = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
  } catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    std::cout << vertex_filepath << std::endl;
    std::cout << fragment_filepath << std::endl;
  }
  const char* v_shader_code = vertex_code.c_str();
  const char* f_shader_code = fragment_code.c_str();

  // 2. compile shaders
  unsigned int vertex   = 0;
  unsigned int fragment = 0;
  int          success  = 0;
  char         info_log[512];
  // vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &v_shader_code, NULL);
  glCompileShader(vertex);
  // print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << info_log << std::endl;
  };
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &f_shader_code, NULL);
  glCompileShader(fragment);
  // print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << info_log << std::endl;
  } else {
    if (verbose) {
      std::cout << "shader successfully compiled" << std::endl;
    }
  }

  // shader Program
  this->program_ID = glCreateProgram();
  glAttachShader(this->program_ID, vertex);
  glAttachShader(this->program_ID, fragment);
  glLinkProgram(this->program_ID);
  // print linking errors if any
  // print linking errors if any
  glGetProgramiv(this->program_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->program_ID, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << info_log << std::endl;
  } else {
    if (verbose) {
      std::cout << "shader successfully linked" << std::endl;
    }
  }
  // delete the shaders as they’re linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

// ------------------------------------------------------------------------
void
Shader::reload(bool verbose) {
  glDeleteProgram(program_ID);
  load(verbose);
}

// ------------------------------------------------------------------------
void
Shader::use() {
  glUseProgram(program_ID);
}

// ------------------------------------------------------------------------
void
Shader::setBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(program_ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void
Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(program_ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void
Shader::setFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(program_ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void
Shader::setMat4fv(const std::string& name, float* mat) const {
  glUniformMatrix4fv(
    glGetUniformLocation(program_ID, name.c_str()), 1, GL_FALSE, mat);
}