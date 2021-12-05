#pragma once

#include "GLShader.h"

class GLBasicShader : public GLShader
{
private:
	static GLVertexShaderLoader vertexShader;
	static GLFragmentShaderLoader fragmentShader;
	static bool initialized;
public:
    GLBasicShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShader = GLVertexShaderLoader("shaders\\BasicVertexShader.glsl");
			fragmentShader = GLFragmentShaderLoader("shaders\\BasicFragmentShader.glsl");

			vertexShader.Load();
			fragmentShader.Load();
		}

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicShader()
	{

	}
};

GLVertexShaderLoader GLBasicShader::vertexShader;
GLFragmentShaderLoader GLBasicShader::fragmentShader;
bool GLBasicShader::initialized = false;

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

			vertexShader = GLVertexShaderLoader("shaders\\BasicMaterialVertexShader.glsl");
			fragmentShader = GLFragmentShaderLoader("shaders\\BasicMaterialFragmentShader.glsl");

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

class GLBasicTextureShader : public GLShader
{
private:
	static GLVertexShaderLoader vertexShader;
	static GLFragmentShaderLoader fragmentShader;
	static bool initialized;
public:
	GLBasicTextureShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShader = GLVertexShaderLoader("shaders\\BasicTextureVertexShader.glsl");
			fragmentShader = GLFragmentShaderLoader("shaders\\BasicTextureFragmentShader.glsl");

			vertexShader.Load();
			fragmentShader.Load();
		}

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicTextureShader()
	{

	}
};

GLVertexShaderLoader GLBasicTextureShader::vertexShader;
GLFragmentShaderLoader GLBasicTextureShader::fragmentShader;
bool GLBasicTextureShader::initialized = false;

class GLBasicTextureMaterialShader : public GLShader
{
private:
	static GLVertexShaderLoader vertexShader;
	static GLFragmentShaderLoader fragmentShader;
	static bool initialized;
public:
	GLBasicTextureMaterialShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShader = GLVertexShaderLoader("shaders\\BasicTextureMaterialVertexShader.glsl");
			fragmentShader = GLFragmentShaderLoader("shaders\\BasicTextureMaterialFragmentShader.glsl");

			vertexShader.Load();
			fragmentShader.Load();
		}

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicTextureMaterialShader()
	{

	}
};

GLVertexShaderLoader GLBasicTextureMaterialShader::vertexShader;
GLFragmentShaderLoader GLBasicTextureMaterialShader::fragmentShader;
bool GLBasicTextureMaterialShader::initialized = false;