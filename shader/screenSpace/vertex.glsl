#version 460 core

layout(location = 0) in vec4 position;

uniform vec4 u_Screen;

mat2 ConvertGLScrene(vec4 Screen) { return mat2(2 / Screen.x, 0, 0, -2 / Screen.y); }

void main() {
    gl_Position = vec4(ConvertGLScrene(u_Screen) * position.xy - vec2(1.0, -1.0), 0.0, 1.0);
}