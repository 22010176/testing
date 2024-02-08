#pragma once

#include <cstdint>
#include <vector>

class VAO {
private:
    uint32_t vao, ibo;
    std::vector<uint32_t> indices;

public:
    VAO();
    ~VAO();
};

