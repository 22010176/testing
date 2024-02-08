#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

#include <glad/glad.h>

#define check glCheckError_(__FILE__, __LINE__)

std::string ReadFile(const std::string& path);
std::vector<std::string> SplitString(const std::string& src, const std::string& temp);
GLenum glCheckError_(const char* file, int line);