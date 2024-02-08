#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdlib>

#include <glad/glad.h>

#include "utilities.h"

void DebugShader(uint32_t shader);
uint32_t GenShader(uint32_t type, const std::string& src);
uint32_t GenProgram(const std::string& vertexShader, const std::string& fragmentShader);
uint32_t CreateProgram(const std::string& path);