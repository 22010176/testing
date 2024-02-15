#define GLFW_INCLUDE_NONE 

#define GLM_ENABLE_EXPERIMENTAL 
#define GLM_FORCE_SWIZZLE 

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

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(-1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  //
  return window;
}

void MainLoop(GLFWwindow* window) {
  Shader shader("./shader/screenSpace");
  Shader shader1("./shader/test");


  float f[]{ width, height, 0.0f, 0.0f };
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT); check;

    shader.SetUniform("u_Screen", f);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
}

void CleanUp() { glfwTerminate(); }

void MainProgram() {
  GLFWwindow* window = Initialize();

  // main loop
  MainLoop(window);

  // clean up
  CleanUp();
}

int main(int argc, char* argv[]) {
  MainProgram();

  return 0;
}

