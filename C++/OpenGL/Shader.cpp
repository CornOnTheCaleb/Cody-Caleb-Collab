#include "Shader.h"

Shader::Shader () : m_program(0)
{

}

Shader::Shader (const std::string vertexShaderFilePathname, const std::string fragmentShaderFilePathname) : Shader()
{
  // Get source code for vertex and fragment shaders from files specified
  bool filesLoadedSuccessfully = true;

  std::string vertexShaderSourceCode;
  std::ifstream vertexShaderFile(vertexShaderFilePathname);
  if (vertexShaderFile.is_open())
  {
    vertexShaderSourceCode = std::string((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
    vertexShaderFile.close();
  }
  else
  {
    filesLoadedSuccessfully = false;
    std::cout << "File for vertex shader (\"" << vertexShaderFilePathname << "\") does not exist!" << std::endl;
  }

  std::string fragmentShaderSourceCode;
  std::ifstream fragmentShaderFile(fragmentShaderFilePathname);
  if (fragmentShaderFile.is_open())
  {
    fragmentShaderSourceCode = std::string((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
    fragmentShaderFile.close();
  }
  else
  {
    filesLoadedSuccessfully = false;
    std::cout << "File for fragment shader (\"" << fragmentShaderFilePathname << "\") does not exist!" << std::endl;
  }

  // Create vertex and fragment shaders from source code
  if (filesLoadedSuccessfully)
  {
    bool shadersCompiledSuccessfully = true;
    int success;       // Used to check if compilation of shaders worked
    char infoLog[512]; // Used to get error messages for failed compilations

    const char * vertexShaderSource = vertexShaderSourceCode.c_str();
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      shadersCompiledSuccessfully = false;
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "Failed to compile vertex shader from source code!" << std::endl << infoLog << std::endl;
    }

    const char * fragmentShaderSource = fragmentShaderSourceCode.c_str();
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      shadersCompiledSuccessfully = false;
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "Failed to compile fragment shader from source code!" << std::endl << infoLog << std::endl;
    }

    // Create shader program from vertex and fragment shaders
    if (shadersCompiledSuccessfully)
    {
      int shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
      glLinkProgram(shaderProgram);
      glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
      if (!success)
      {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Failed to link shader program!" << std::endl << infoLog << std::endl;
      }
      else
      {
        m_program = shaderProgram;
      }
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
    }
  }
}


Shader::~Shader ()
{
  glDeleteProgram(m_program);
  m_program = 0;
}

void Shader::use () const
{
  glUseProgram(m_program);
}

void Shader::set_bool (const std::string name, const bool value) const
{
  glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);
}

void Shader::set_int (const std::string name, const int value) const
{
  glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::set_float (const std::string name, const float value) const
{
  glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::set_matrix4 (const std::string name, const glm::mat4 value) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_vector4 (const std::string name, const glm::vec4 value) const
{
  glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr(value));
}

int Shader::get_program () const
{
  return m_program;
}