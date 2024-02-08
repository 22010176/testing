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
#include <Shader.h>

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
  uint32_t program = CreateProgram("./shader/screenSpace");
  glUseProgram(program); check;
  int screen = glGetUniformLocation(program, "u_Screen"); check;

  uint32_t vao, ibo, vbo;
  glGenVertexArrays(1, &vao); check;
  glBindVertexArray(vao); check;

  glGenBuffers(1, &ibo); check;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); check;
  std::vector<uint32_t> indexes{ 0,1,2 };
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint32_t), indexes.data(), GL_DYNAMIC_DRAW); check;

  glGenBuffers(1, &vbo); check;
  glBindBuffer(GL_ARRAY_BUFFER, vbo); check;
  std::vector<float> positions2{ 0.0f, 0.0f, width, height, 0.0f, height };
  glBufferData(GL_ARRAY_BUFFER, positions2.size() * sizeof(float), positions2.data(), GL_DYNAMIC_DRAW); check;

  glEnableVertexAttribArray(0); check;
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), NULL); check;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT); check;

    glUniform4f(screen, width, height, 0.0, 0.0); check;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); check;

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
  MainProgram();
  glm::mat2 m2(2 / width, 0, 0, -2 / height);
  std::vector<glm::vec2> positions2{ {0.0f, 0.0f}, {width, height}, {0.0f, height} };
  for (glm::vec2& v : positions2) {
    std::cout << glm::to_string(m2 * v - glm::vec2(1.0, -1.0)) << std::endl;
  }
  return 0;
}

