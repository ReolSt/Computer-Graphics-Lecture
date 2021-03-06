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
	GLShaderLoader() 
		: Id(-1) { }

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

	unsigned int Id;
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
	static std::shared_ptr<GLShader> GetDefaultShader()
	{
		static std::string vertexSource =
			"#version 330 core\n"
			"layout(location = 0) in vec4 in_Position;\n"
			"layout(location = 1) in vec4 in_Color;\n"
			"out vec4 out_Color;\n"
			"uniform mat4 cameraMatrix;\n"
			"uniform mat4 modelMatrix;\n"
			"void main() {\n"
			"    gl_Position = cameraMatrix * modelMatrix * in_Position;\n"
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

		return GLCreate<GLShader>(vertexShader, fragmentShader);
	}
public:
	GLShader() 
		: Id(-1) { }

	GLShader(GLVertexShaderLoader vertexShader, GLFragmentShaderLoader fragmentShader)
	{
		this->CreateProgram(vertexShader, fragmentShader);
	}

	GLShader(const std::string& vertexFilename, const std::string& fragmentFilename)
	{
		this->Load(vertexFilename, fragmentFilename);
	}

	~GLShader()
	{
		glDeleteProgram(this->Id);
	}

	void Load(const std::string& vertexFilename, const std::string& fragmentFilename)
	{
		GLVertexShaderLoader vertexShaderLoader(vertexFilename);
		GLFragmentShaderLoader fragmentShaderLoader(fragmentFilename);

		this->CreateProgram(vertexShaderLoader, fragmentShaderLoader);
	}

	unsigned int GetId()
	{
		return this->Id;
	}

	int GetUniformLocation(const std::string& name)
	{
		if (this->UniformLocations.find(name) == this->UniformLocations.end())
		{
			this->UniformLocations[name] = glGetUniformLocation(this->GetId(), name.c_str());
		}

		return this->UniformLocations[name];
	}

	template <typename T>
	void SetUniform(const std::string& name, T value)
	{
		return;
	}

	void SetUniform(const std::string& name, int value)
	{
		glUniform1i(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, const glm::tvec2<int>& value)
	{
		glUniform2i(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, const glm::tvec3<int>& value)
	{
		glUniform3i(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, const glm::tvec4<int>& value)
	{
		glUniform4i(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, unsigned int value)
	{
		glUniform1ui(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, const glm::tvec2<unsigned int>& value)
	{
		glUniform2ui(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, const glm::tvec3<unsigned int>& value)
	{
		glUniform3ui(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, const glm::tvec4<unsigned int>& value)
	{
		glUniform4ui(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, GLfloat value)
	{
		glUniform1f(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, const glm::tvec2<GLfloat>& value)
	{
		glUniform2f(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, const glm::tvec3<GLfloat>& value)
	{
		glUniform3f(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, const glm::tvec4<GLfloat>& value)
	{
		glUniform4f(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, GLdouble value)
	{
		glUniform1d(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, const glm::tvec2<GLdouble>& value)
	{
		glUniform2d(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, const glm::tvec3<GLdouble>& value)
	{
		glUniform3d(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, const glm::tvec4<GLdouble>& value)
	{
		glUniform4d(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, glm::tmat2x2<GLfloat> value)
	{
		glUniformMatrix2fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat2x3<GLfloat> value)
	{
		glUniformMatrix2x3fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat2x4<GLfloat> value)
	{
		glUniformMatrix2x4fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x2<GLfloat> value)
	{
		glUniformMatrix3x2fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x3<GLfloat> value)
	{
		glUniformMatrix3fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x4<GLfloat> value)
	{
		glUniformMatrix3x4fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x2<GLfloat> value)
	{
		glUniformMatrix4x2fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x3<GLfloat> value)
	{
		glUniformMatrix4x3fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x4<GLfloat> value)
	{
		glUniformMatrix4fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat2x2<GLdouble> value)
	{
		glUniformMatrix2dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat2x3<GLdouble> value)
	{
		glUniformMatrix2x3dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat2x4<GLdouble> value)
	{
		glUniformMatrix2x4dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x2<GLdouble> value)
	{
		glUniformMatrix3x2dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x3<GLdouble> value)
	{
		glUniformMatrix3dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat3x4<GLdouble> value)
	{
		glUniformMatrix3x4dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x2<GLdouble> value)
	{
		glUniformMatrix4x2dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x3<GLdouble> value)
	{
		glUniformMatrix4x3dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetUniform(const std::string& name, glm::tmat4x4<GLdouble> value)
	{
		glUniformMatrix4dv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
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

		this->Id = glCreateProgram();
		glAttachShader(this->Id, vertexShaderLoader.GetId());
		glAttachShader(this->Id, fragmentShaderLoader.GetId());
		glLinkProgram(this->Id);

		glGetProgramiv(this->Id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Id, 1024, NULL, infoLog);
			std::cout << "GLShader: Program Linking Error" << std::endl;
			std::cout << infoLog << std::endl;
		}

		glDeleteShader(vertexShaderLoader.GetId());
		glDeleteShader(fragmentShaderLoader.GetId());
	}

private:
	unsigned int Id;

	std::unordered_map<std::string, int> UniformLocations;
};