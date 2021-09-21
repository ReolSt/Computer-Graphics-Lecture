#version 330 core

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Color;

out vec4 out_Color;

void main()
{
	gl_Position = in_Position;

	out_Color = in_Color;
}
