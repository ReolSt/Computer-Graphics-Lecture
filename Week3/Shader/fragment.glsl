#version 330

in vec4 out_Color;
out vec4 fragColor;

void main()
{
	fragColor = vec4(out_Color);
}
