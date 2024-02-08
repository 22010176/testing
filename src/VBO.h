#pragma once

#include <cstdint>

#include <glad/glad.h>

struct RenderObject {
    uint32_t vao;
    uint32_t program;
};

class VBO {
private:
    /* data */
public:
    VBO();
    ~VBO();
};
