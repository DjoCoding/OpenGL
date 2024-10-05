#version 410 core 

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aColor;

out vec3 Color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {  
    gl_Position = Projection * View * Model * vec4(aPosition, 1.0f);
    Color = aColor;
}