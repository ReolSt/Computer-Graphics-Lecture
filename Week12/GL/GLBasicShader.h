#pragma once

#include "GLShader.h"

class GLBasicShader : public GLShader
{
public:
    GLBasicShader()
	{
		static std::string vertexSource =
			"#version 330 core\n"
			"layout(location = 0) in vec4 in_Position;\n"
			"layout(location = 1) in vec4 in_Color;\n"
			"layout(location = 2) in vec4 in_Normal;\n"
			"out vec4 out_Color;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"    gl_Position = projection * view * model * in_Position;\n"
			"    out_Color = in_Color;\n"
			"}\n";

		static std::string fragmentSource =
			"#version 330 core\n"
			"in vec4 out_Color;\n"
			"out vec4 fragColor;\n"
			"void main() {\n"
			"    fragColor = vec4(out_Color);\n"
			"}\n";

		GLVertexShaderLoader vertexShader;
		vertexShader.SetSource(vertexSource);
		vertexShader.Load();

		GLFragmentShaderLoader fragmentShader;
		fragmentShader.SetSource(fragmentSource);
		fragmentShader.Load();

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicShader()
	{
		glDeleteProgram(this->GetId());
	}
};

class GLBasicMaterialShader : public GLShader
{
private:
	static GLVertexShaderLoader vertexShader;
	static GLFragmentShaderLoader fragmentShader;
	static bool initialized;
public:
	GLBasicMaterialShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShader = GLVertexShaderLoader("Shader\\BasicMaterialVertexShader.glsl");
			fragmentShader = GLFragmentShaderLoader("Shader\\BasicMaterialFragmentShader.glsl");

			vertexShader.Load();
			fragmentShader.Load();
		}

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicMaterialShader()
	{

	}
};

GLVertexShaderLoader GLBasicMaterialShader::vertexShader;
GLFragmentShaderLoader GLBasicMaterialShader::fragmentShader;
bool GLBasicMaterialShader::initialized = false;