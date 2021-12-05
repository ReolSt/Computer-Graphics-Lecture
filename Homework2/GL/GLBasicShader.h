#pragma once

#include "GLShader.h"

class GLBasicShader : public GLShader
{
private:
	static GLShaderLoader vertexShaderSource;
	static GLShaderLoader fragmentShaderSource;
	static bool initialized;
public:
    GLBasicShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShaderSource = GLShaderLoader("shaders\\BasicVertexShader.glsl");
			fragmentShaderSource = GLShaderLoader("shaders\\BasicFragmentShader.glsl");
		}

		GLVertexShaderLoader vertexShader;
		GLFragmentShaderLoader fragmentShader;

		vertexShader.SetSource(vertexShaderSource.GetSource());
		fragmentShader.SetSource(fragmentShaderSource.GetSource());

		vertexShader.Load();
		fragmentShader.Load();

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicShader()
	{

	}
};

GLShaderLoader GLBasicShader::vertexShaderSource;
GLShaderLoader GLBasicShader::fragmentShaderSource;
bool GLBasicShader::initialized = false;

class GLBasicMaterialShader : public GLShader
{
private:
	static GLShaderLoader vertexShaderSource;
	static GLShaderLoader fragmentShaderSource;
	static bool initialized;
public:
	GLBasicMaterialShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShaderSource = GLShaderLoader("shaders\\BasicMaterialVertexShader.glsl");
			fragmentShaderSource = GLShaderLoader("shaders\\BasicMaterialFragmentShader.glsl");
		}

		GLVertexShaderLoader vertexShader;
		GLFragmentShaderLoader fragmentShader;

		vertexShader.SetSource(vertexShaderSource.GetSource());
		fragmentShader.SetSource(fragmentShaderSource.GetSource());

		vertexShader.Load();
		fragmentShader.Load();

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicMaterialShader()
	{

	}
};

GLShaderLoader GLBasicMaterialShader::vertexShaderSource;
GLShaderLoader GLBasicMaterialShader::fragmentShaderSource;
bool GLBasicMaterialShader::initialized = false;

class GLBasicTextureShader : public GLShader
{
private:
	static GLShaderLoader vertexShaderSource;
	static GLShaderLoader fragmentShaderSource;
	static bool initialized;
public:
	GLBasicTextureShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShaderSource = GLShaderLoader("shaders\\BasicTextureVertexShader.glsl");
			fragmentShaderSource = GLShaderLoader("shaders\\BasicTextureFragmentShader.glsl");
		}

		GLVertexShaderLoader vertexShader;
		GLFragmentShaderLoader fragmentShader;

		vertexShader.SetSource(vertexShaderSource.GetSource());
		fragmentShader.SetSource(fragmentShaderSource.GetSource());

		vertexShader.Load();
		fragmentShader.Load();

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicTextureShader()
	{

	}
};

GLShaderLoader GLBasicTextureShader::vertexShaderSource;
GLShaderLoader GLBasicTextureShader::fragmentShaderSource;
bool GLBasicTextureShader::initialized = false;

class GLBasicTextureMaterialShader : public GLShader
{
private:
	static GLShaderLoader vertexShaderSource;
	static GLShaderLoader fragmentShaderSource;
	static bool initialized;
public:
	GLBasicTextureMaterialShader()
	{
		if (!initialized)
		{
			initialized = true;

			vertexShaderSource = GLShaderLoader("shaders\\BasicTextureMaterialVertexShader.glsl");
			fragmentShaderSource = GLShaderLoader("shaders\\BasicTextureMaterialFragmentShader.glsl");
		}

		GLVertexShaderLoader vertexShader;
		GLFragmentShaderLoader fragmentShader;

		vertexShader.SetSource(vertexShaderSource.GetSource());
		fragmentShader.SetSource(fragmentShaderSource.GetSource());

		vertexShader.Load();
		fragmentShader.Load();

		this->CreateProgram(vertexShader, fragmentShader);
	}

	virtual ~GLBasicTextureMaterialShader()
	{

	}
};

GLShaderLoader GLBasicTextureMaterialShader::vertexShaderSource;
GLShaderLoader GLBasicTextureMaterialShader::fragmentShaderSource;
bool GLBasicTextureMaterialShader::initialized = false;