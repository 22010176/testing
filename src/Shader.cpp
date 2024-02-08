#include "Shader.h"

Shader::Shader(const std::string& path) : program(CreateProgram(path)) {
    this->AddUniform(ReadFile(path + "/vertex.glsl"));
}
Shader::Shader(const std::string& vertex, const std::string& fragment) : program(GenProgram(vertex, fragment)) {
    this->AddUniform(ReadFile(vertex));
}
Shader::~Shader() { glDeleteProgram(this->program); check; }

void Shader::AddUniform(const std::string& shader) {
    this->Bind();
    std::vector<std::string> u = GetUniforms(shader);

    for (std::string& uni : u) {
        this->uniforms[uni] = glGetUniformLocation(this->program, uni.c_str()); check;
    }
}

uint32_t Shader::GetProgram() const { return this->program; }
std::map<std::string, uint32_t> Shader::GetKeys() const { return this->uniforms; }

void Shader::SetUniform(const std::string& name, float* val) {
    this->Bind();
    if (this->uniforms.find(name.c_str()) == this->uniforms.end()) return;
    glUniform4fv(this->uniforms[name], 1, val); check;
}

void Shader::Bind() { glUseProgram(this->program); check; }
void Shader::Unbind() { glUseProgram(0); check; }

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
    std::cout << infoLog.data() << std::endl;

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

std::vector<std::string> GetUniforms(const std::string& src) {
    std::vector<std::string> str = SplitString(src, "\n");
    std::vector<std::string> res{};

    for (std::string& s : str) if (s.find("//") == std::string::npos && s.find("uniform") != std::string::npos)
        res.push_back(SplitString(s.substr(0, s.size() - 1), " ").back());

    return res;
}