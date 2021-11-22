#version 330 core

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec4 in_Normal;

out vec3 fragPos;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position	= projection * view * model * in_Position;
    fragPos = vec3(model * in_Position);
    normal = vec3(in_Normal);
}