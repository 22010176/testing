#include "Shader.h"

void DebugShader(uint32_t shader) {
    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled); check;

    if (isCompiled) return;

    int maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); check;

    // The maxLength includes the NULL character
    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]); check;

    // We don't need the shader anymore.
    glDeleteShader(shader); check;

    // Use the infoLog as you see fit.
    std::cout << infoLog.data();

    // In this simple program, we'll just leave
    exit(-1);
}

uint32_t GenShader(uint32_t type, const std::string& src) {
    uint32_t shader = glCreateShader(type); check;

    const char* s = src.c_str();

    glShaderSource(shader, 1, &s, 0); check;
    glCompileShader(shader); check;

    DebugShader(shader);

    return shader;
}

uint32_t GenProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    uint32_t program = glCreateProgram(); check;

    uint32_t v = GenShader(GL_VERTEX_SHADER, vertexShader); check;
    uint32_t f = GenShader(GL_FRAGMENT_SHADER, fragmentShader); check;

    glAttachShader(program, v); check;
    glAttachShader(program, f); check;
    glLinkProgram(program); check;

    glDetachShader(program, v); check;
    glDetachShader(program, f); check;

    glDeleteShader(v); check;
    glDeleteShader(f); check;

    return program;
}

uint32_t CreateProgram(const std::string& path) { return GenProgram(ReadFile(path + "/vertex.glsl"), ReadFile(path + "/fragment.glsl")); }