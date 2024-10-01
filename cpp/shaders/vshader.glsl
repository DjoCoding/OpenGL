#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float uOffset;

out vec3 Color;

void main() {
    gl_Position = vec4(aPos.x, aPos.y + uOffset, aPos.z, 1.0);
    Color = aColor;
}