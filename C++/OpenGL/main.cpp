#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Renderer.h"
#include "GameManager.h"

#include "Utility.h"

void framebuffer_size_callback (GLFWwindow * window, int width, int height);

// Window settings
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "OpenGL Stuff";

int main ()
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // THE FOLLOWING INITIALIZES OPENGL AND CREATES THE WINDOW. KEEP THIS AT THE TOP OF MAIN THREAD OR SUFFER THE CONSEQUENCES. //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow * window = glfwCreateWindow (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window!" << std::endl;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD!" << std::endl;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  rand_seed();

  GameManager gameManager(window);
  gameManager.start_game();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback (GLFWwindow * window, int width, int height)
{
  glViewport(0, 0, width, height);
}
