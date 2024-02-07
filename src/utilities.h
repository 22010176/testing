#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

std::string ReadFile(const std::string& path);

std::vector<std::string> SplitString(const std::string& src, const std::string& temp);