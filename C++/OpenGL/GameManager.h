#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Renderer.h"

#include "Utility.h"

class GameManager
{
private:
  GLFWwindow * m_window;

  std::map< std::string, Shader* > m_shaders;
  std::map< std::string, Texture* > m_textures;
  std::vector< std::pair< Object*, bool> > m_objects;

  Renderer * m_renderer;
  Camera * m_camera;

  // Game stats
  int m_fps;
public:
  // Constructor
  GameManager (GLFWwindow * window);

  // Clean up
  ~GameManager ();

  // Do the game
  void start_game ();
private:
  // Operations on a per frame basis
  void tick (const float deltaTime);

  // Process user input
  void process_input (const float deltaTime);

  // Check if 2D objects collided
  bool check_collision (Object & object1, Object & object2);
};

#endif
