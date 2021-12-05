#version 330 core

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec4 in_Normal;
layout(location = 3) in vec2 in_UV;                                                                                                                                                                                                                                                                                                                                                                                                                                                                   

out vec3 fragPosition;
out vec3 normal;
out vec3 viewPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

varying mat4 viewMatrix;
varying mat4 projectionMatrix;

void main()
{
    vec4 worldPos = model * in_Position;
    gl_Position	= projection * view * worldPos;

    fragPosition = worldPos.xyz;
    viewPosition = cameraPosition;

    normal = mat3(transpose(inverse(model))) * vec3(in_Normal);

    viewMatrix = view;
    projectionMatrix = projection;
}