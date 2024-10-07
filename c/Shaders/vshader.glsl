#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 MODEL;

out vec3 fColor;

void main() {
    gl_Position = MODEL * vec4(aPosition, 1.0);
    fColor = aColor;
}