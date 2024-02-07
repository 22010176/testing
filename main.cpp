#define GLM_ENABLE_EXPERIMENTAL 
#define GLM_FORCE_SWIZZLE 
#define GLFW_INCLUDE_NONE 

#include "bits/stdc++.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <utilities.h>

float width = 1920 / 2, height = 1080 / 2;

GLFWwindow* Initialize() {
  /* Initialize the library */
  if (!glfwInit()) exit(-1);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(-1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  return window;
}

void MainLoop(GLFWwindow* window) {
  uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
  uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


  std::string vSrc = ReadFile("./shader/test/vertex.glsl");
  std::string fSrc = ReadFile("./shader/test/fragment.glsl");

  const char* a = vSrc.c_str(), * b = fSrc.c_str();

  glShaderSource(vertexShader, 1, &a, nullptr);
  glShaderSource(fragmentShader, 1, &b, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  uint32_t program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glUseProgram(program);

  uint32_t screen = glGetUniformLocation(program, "Screen");

  uint32_t vao, ibo, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  std::vector<uint32_t> indexes{ 0,1,2 };
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint32_t), indexes.data(), GL_DYNAMIC_DRAW);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  std::vector<float> positions{ 0.0f, 0.0f, width, height, 0.0f,height };
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), NULL);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glUniform2f(screen, width, height);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
}

void CleanUp() { glfwTerminate(); }

void MainProgram() {
  GLFWwindow* window = Initialize();

  MainLoop(window);

  CleanUp();
}

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  MainProgram();

  return 0;
}

