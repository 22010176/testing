#include "utilities.h"

std::string ReadFile(const std::string& path) {
  std::ifstream file(path);

  std::string result, line;
  while (std::getline(file, line)) result = result + line.c_str() + '\n';

  return result;
}

std::vector<std::string> SplitString(const std::string& src, const std::string& temp) {
  if (src.size() == 0) return {};

  std::string _src = src;
  std::vector<std::string> result;

  while (_src.find(temp) != std::string::npos) {
    int index = _src.find(temp);
    std::string sub = _src.substr(0, index);

    if (sub.size() > 0) result.push_back(sub);
    _src = _src.substr(index + 1, src.size() - index);
  }
  result.push_back(_src);

  return result;
}

GLenum glCheckError_(const char* file, int line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (errorCode) {
    case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
    case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
    case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
    }
    std::cout << error << " | " << file << "#" << line << std::endl;
    exit(-1);
  }
  return errorCode;
}