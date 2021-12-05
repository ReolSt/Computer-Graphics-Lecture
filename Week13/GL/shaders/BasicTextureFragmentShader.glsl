#version 330 core

struct Material
{
    sampler2D diffuse;
};

uniform Material material;

in vec4 outColor;
in vec2 texCoords;

out vec4 fragColor;

void main()
{
    fragColor = texture(material.diffuse, texCoords);
}