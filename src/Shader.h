#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>

#include <glad/glad.h>

#include "utilities.h"

class Shader {
private:
    uint32_t program;
    std::map<std::string, uint32_t> uniforms;

    void AddUniform(const std::string& shader);

public:
    Shader(const std::string& path);
    Shader(const std::string& vertex, const std::string& fragment);
    ~Shader();

    uint32_t GetProgram() const;
    std::map<std::string, uint32_t> GetKeys() const;

    void SetUniform(const std::string& name, float* val);

    void Bind();
    void Unbind();
};

void DebugShader(uint32_t shader);
uint32_t GenShader(uint32_t type, const std::string& src);
uint32_t GenProgram(const std::string& vertexShader, const std::string& fragmentShader);
uint32_t CreateProgram(const std::string& path);
std::vector<std::string> GetUniforms(const std::string& src);