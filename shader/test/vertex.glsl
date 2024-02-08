#version 460 core

uniform vec4 Screen;

layout(location = 0) in vec4 position;

void main(){
    // gl_Position = vec4(position.x * 2.0 / Screen.x - 1.0, -position.y * 2.0 / Screen.y + 1.0, 0.0, 0.0);
    gl_Position = position;
}
