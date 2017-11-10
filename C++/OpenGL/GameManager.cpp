#include "GameManager.h"

GameManager::GameManager (GLFWwindow * window) : m_window(window)
{
  // Load shaders
  m_shaders["basic"] = new Shader("Resources/Shaders/vertexShader.txt", "Resources/Shaders/fragmentShader.txt");
  m_shaders["text"] = new Shader("Resources/Shaders/TextVertexShader.txt", "Resources/Shaders/TextFragmentShader.txt");

  // Load textures
  m_textures["background"] = new Texture("Resources/Images/background.png");
  m_textures["bitmapFont"] = new Texture("Resources/Images/text.png", false);
  m_textures["smileyFace"] = new Texture("Resources/Images/smile.png");
  m_textures["square"] = new Texture("Resources/Images/square.png", false);
  m_textures["wall"] = new Texture("Resources/Images/wall.jpg");

  // Load renderer
  m_renderer = new Renderer(m_window, *m_shaders["basic"], *m_shaders["text"], *m_textures["bitmapFont"]);

  // Load camera
  m_camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
  m_camera->set_projection_mode(PERSPECTIVE);

  // Load objects
  // m_objects.push_back(std::pair< Object*, bool >(new Object(*m_textures["background"], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 1.0f)), false));
  m_objects.push_back(std::pair< Object*, bool >(new Object(*m_textures["smileyFace"], glm::vec3(0.0f, 0.0f, 0.5f)), true));
  m_objects.push_back(std::pair< Object*, bool >(new Object(*m_textures["wall"], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f)), true));
}


GameManager::~GameManager()
{
  for (auto shader : m_shaders)
  {
    delete shader.second;
  }
  m_shaders.clear();

  for (auto texture : m_textures)
  {
    delete texture.second;
  }
  m_textures.clear();

  for (auto object : m_objects)
  {
    delete object.first;
  }
  m_objects.clear();

  delete m_renderer;
  m_renderer = NULL;

  delete m_camera;
  m_camera = NULL;
}

void GameManager::start_game ()
{
  float currentTime = (float)glfwGetTime();
  float previousTime = currentTime;
  float deltaTime = currentTime - previousTime;
  float lastFPSCheckTime = currentTime;
  int frames = 0;
  int fps = 0;
  int total = 0;
  m_fps = 0;
  while (!glfwWindowShouldClose(m_window))
  {
    currentTime = (float)glfwGetTime();
    deltaTime = currentTime - previousTime;

    process_input(deltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tick(deltaTime);

    if (currentTime - lastFPSCheckTime >= 0.1f)
    {
      fps += (int)(frames / (currentTime - lastFPSCheckTime));
      ++total;
      m_fps = fps / total;
      lastFPSCheckTime = currentTime;
      frames = 0;
    }

    glfwSwapBuffers(m_window);
    glfwPollEvents();

    previousTime = currentTime;
    ++frames;
  }
}

void GameManager::tick (const float deltaTime)
{
  std::vector< std::pair< Object*, bool > >::iterator end = m_objects.end();
  for (std::vector< std::pair< Object*, bool > >::iterator i = m_objects.begin(); i != end; i++)
  {
    Object * object = i->first;
    bool usesCollision = i->second;
    m_renderer->render_basic(*object, *m_camera);
    if (usesCollision)
    {
      for (std::vector< std::pair< Object*, bool > >::iterator j = i + 1; j != end; j++)
      {
        Object * otherObject = j->first;
        bool otherUsesCollision = j->second;
        if (otherUsesCollision && check_collision(*object, *otherObject))
        {
          // Process collision
        }
      }
    }
  }
  m_renderer->render_text_beta("fps: " + std::to_string(m_fps), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(-1.0f, 0.95f), glm::vec2(0.025f, 0.05f));
}

void GameManager::process_input (const float deltaTime)
{
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(m_window, true);
  }
  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() + m_camera->get_front() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() - m_camera->get_front() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() + m_camera->get_right() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() - m_camera->get_right() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() + m_camera->get_up() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    m_camera->set_position(m_camera->get_position() - m_camera->get_up() * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
  {
    m_camera->set_rotation(m_camera->get_rotation() + glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    m_camera->set_rotation(m_camera->get_rotation() - glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    m_camera->set_rotation(m_camera->get_rotation() + glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime);
  }
  if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    m_camera->set_rotation(m_camera->get_rotation() - glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime);
  }
}

bool GameManager::check_collision (Object & object1, Object & object2)
{
  // ASSUMES NO ROTATION
  glm::vec3 position1 = object1.get_position();
  glm::vec3 position2 = object2.get_position();
  glm::vec3 size1 = object1.get_size();
  glm::vec3 size2 = object2.get_size();
  bool collisionX = (position1.x + size1.x / 2 >= position2.x - size2.x / 2 || position2.x + size2.x / 2 >= position1.x - size1.x / 2);
  bool collisionY = (position1.y + size1.y / 2 >= position2.y - size2.y / 2 || position2.y + size2.y / 2 >= position1.y - size1.y / 2);
  return (collisionX && collisionY);
}