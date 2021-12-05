#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtc/type_ptr.hpp>

#include "GLMemoryHelpers.h"

class GLShaderLoader
{
public:
	GLShaderLoader() { }

	GLShaderLoader(const std::string& filename)
	{
		this->LoadFile(filename);
	}

	virtual ~GLShaderLoader()
	{
		if (this->Id >= 0)
		{
			glDeleteShader(this->Id);
		}
	}

	virtual void LoadFile(const std::string& filename)
	{
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			file.open(filename);

			std::stringstream stream;
			stream << file.rdbuf();

			file.close();

			this->Source = stream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "GLShader : File Read Error." << std::endl;
		}
	}

	const std::string& GetSource()
	{
		return this->Source;
	}

	void SetSource(const std::string& source)
	{
		this->Source = source;
	}

	virtual void Load() { }

	unsigned int GetId()
	{
		return this->Id;
	}

	std::string GetCode()
	{
		return this->Source;
	}
protected:
	std::string Source;

	unsigned int Id = -1;
};

class GLVertexShaderLoader : public GLShaderLoader
{
public:
	GLVertexShaderLoader()
		: GLShaderLoader() { }

	GLVertexShaderLoader(const std::string& filename)
		: GLShaderLoader(filename)
	{
		this->Load();
	}

	void Load() override
	{
		int Success;
		char InfoLog[1024];

		const char* Source = this->Source.c_str();

		this->Id = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(this->GetId(), 1, &Source, NULL);
		glCompileShader(this->GetId());

		glGetShaderiv(this->GetId(), GL_COMPILE_STATUS, &Success);
		if (!Success)
		{
			glGetShaderInfoLog(this->GetId(), 1024, NULL, InfoLog);
			std::cout << "GLVertexShader: Vertex Shader Compile Error" << std::endl;
			std::cout << InfoLog << std::endl;
		}
	}
};

class GLFragmentShaderLoader : public GLShaderLoader
{
public:
	GLFragmentShaderLoader() 
		: GLShaderLoader() { }

	GLFragmentShaderLoader(const std::string& filename)
		: GLShaderLoader(filename)
	{
		this->Load();
	}

	void Load() override
	{
		int success;
		char infoLog[1024];

		const char* source = this->Source.c_str();

		this->Id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->GetId(), 1, &source, NULL);
		glCompileShader(this->GetId());

		glGetShaderiv(this->GetId(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->GetId(), 1024, NULL, infoLog);
			std::cout << "GLFragmentShader: Fragment Shader Compile Error" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
};


class GLShader
{
public:
	GLShader() { }

	GLShader(GLVertexShaderLoader vertexShader, GLFragmentShaderLoader fragmentShader)
	{
		this->CreateProgram(vertexShader, fragmentShader);
	}

	GLShader(const std::string& vertexFilename, const std::string& fragmentFilename)
	{
		this->Load(vertexFilename, fragmentFilename);
	}

	virtual ~GLShader()
	{
		glDeleteProgram(this->id);
	}

	void Load(const std::string& vertexFilename, const std::string& fragmentFilename)
	{
		GLVertexShaderLoader vertexShaderLoader(vertexFilename);
		GLFragmentShaderLoader fragmentShaderLoader(fragmentFilename);

		this->CreateProgram(vertexShaderLoader, fragmentShaderLoader);
	}

	unsigned int GetId()
	{
		return this->id;
	}

	int GetUniformLocation(const std::string& name)
	{
		if (this->uniformLocations.find(name) == this->uniformLocations.end())
		{
			int location = glGetUniformLocation(this->GetId(), name.c_str());

			if (location >= 0)
			{
				this->uniformLocations[name] = location;
			}
			else
			{
				return -1;
			}
		}

		return this->uniformLocations[name];
	}

	template <typename T>
	void SetUniform(const std::string& name, T value)
	{
		SetUniform(this->GetUniformLocation(name.c_str()), value);
	}   

	void SetUniform(int uniformLocation, int value)
	{
		glUniform1i(uniformLocation, value);
	}

	void SetUniform(int uniformLocation, const glm::tvec2<int>& value)
	{
		glUniform2i(uniformLocation, value.x, value.y);
	}

	void SetUniform(int uniformLocation, const glm::tvec3<int>& value)
	{
		glUniform3i(uniformLocation, value.x, value.y, value.z);
	}

	void SetUniform(int uniformLocation, const glm::tvec4<int>& value)
	{
		glUniform4i(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void SetUniform(int uniformLocation, unsigned int value)
	{
		glUniform1ui(uniformLocation, value);
	}

	void SetUniform(int uniformLocation, const glm::tvec2<unsigned int>& value)
	{
		glUniform2ui(uniformLocation, value.x, value.y);
	}

	void SetUniform(int uniformLocation, const glm::tvec3<unsigned int>& value)
	{
		glUniform3ui(uniformLocation, value.x, value.y, value.z);
	}

	void SetUniform(int uniformLocation, const glm::tvec4<unsigned int>& value)
	{
		glUniform4ui(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void SetUniform(int uniformLocation, GLfloat value)
	{
		glUniform1f(uniformLocation, value);
	}

	void SetUniform(int uniformLocation, const glm::tvec2<GLfloat>& value)
	{
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void SetUniform(int uniformLocation, const glm::tvec3<GLfloat>& value)
	{
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void SetUniform(int uniformLocation, const glm::tvec4<GLfloat>& value)
	{
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void SetUniform(int uniformLocation, GLdouble value)
	{
		glUniform1d(uniformLocation, value);
	}

	void SetUniform(int uniformLocation, const glm::tvec2<GLdouble>& value)
	{
		glUniform2d(uniformLocation, value.x, value.y);
	}

	void SetUniform(int uniformLocation, const glm::tvec3<GLdouble>& value)
	{
		glUniform3d(uniformLocation, value.x, value.y, value.z);
	}

	void SetUniform(int uniformLocation, const glm::tvec4<GLdouble>& value)
	{
		glUniform4d(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void SetUniform(int uniformLocation, glm::tmat2x2<GLfloat> value)
	{
		glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat2x3<GLfloat> value)
	{
		glUniformMatrix2x3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat2x4<GLfloat> value)
	{
		glUniformMatrix2x4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x2<GLfloat> value)
	{
		glUniformMatrix3x2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x3<GLfloat> value)
	{
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x4<GLfloat> value)
	{
		glUniformMatrix3x4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x2<GLfloat> value)
	{
		glUniformMatrix4x2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x3<GLfloat> value)
	{
		glUniformMatrix4x3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x4<GLfloat> value)
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat2x2<GLdouble> value)
	{
		glUniformMatrix2dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat2x3<GLdouble> value)
	{
		glUniformMatrix2x3dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat2x4<GLdouble> value)
	{
		glUniformMatrix2x4dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x2<GLdouble> value)
	{
		glUniformMatrix3x2dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x3<GLdouble> value)
	{
		glUniformMatrix3dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat3x4<GLdouble> value)
	{
		glUniformMatrix3x4dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x2<GLdouble> value)
	{
		glUniformMatrix4x2dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x3<GLdouble> value)
	{
		glUniformMatrix4x3dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(int uniformLocation, glm::tmat4x4<GLdouble> value)
	{
		glUniformMatrix4dv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Use()
	{
		glUseProgram(this->GetId());
	}

protected:
	void CreateProgram(GLVertexShaderLoader vertexShaderLoader, GLFragmentShaderLoader fragmentShaderLoader)
	{
		int success;
		char infoLog[1024];

		this->id = glCreateProgram();
		glAttachShader(this->id, vertexShaderLoader.GetId());
		glAttachShader(this->id, fragmentShaderLoader.GetId());
		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(this->id, 1024, NULL, infoLog);
			std::cout << "GLShader: Program Linking Error" << std::endl;
			std::cout << infoLog << std::endl;
		}

		glDeleteShader(vertexShaderLoader.GetId());
		glDeleteShader(fragmentShaderLoader.GetId());
	}

private:
	unsigned int id = -1;

	std::unordered_map<std::string, int> uniformLocations;
};