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

GLFWwindow* Initialize() {
    /* Initialize the library */
    if (!glfwInit()) exit(-1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    return window;
}

void MainLoop(GLFWwindow* window) {
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void CleanUp() {
    glfwTerminate();
}

int main(int argc, char* argv[]) {
    GLFWwindow* window = Initialize();

    MainLoop(window);

    CleanUp();
    return 0;
}

