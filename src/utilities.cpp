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