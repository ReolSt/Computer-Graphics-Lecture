#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>

class GLShaderLoader
{
public:
	GLShaderLoader() 
		: id(-1) { }

	GLShaderLoader(const std::string& file_name)
	{
		this->LoadFile(file_name);
	}

	virtual ~GLShaderLoader()
	{
		if (this->id >= 0)
		{
			glDeleteShader(this->id);
		}
	}

	virtual void LoadFile(const std::string& file_name)
	{
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			file.open(file_name);

			std::stringstream stream;
			stream << file.rdbuf();

			file.close();

			this->source = stream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "GLShader : File Read Error." << std::endl;
		}
	}

	const std::string& GetSource()
	{
		return this->source;
	}

	void SetSource(const std::string& source)
	{
		this->source = source;
	}

	virtual void Load() { }

	unsigned int GetId()
	{
		return this->id;
	}

	std::string GetCode()
	{
		return this->source;
	}
protected:
	std::string source;

	unsigned int id;
};

class GLVertexShaderLoader : public GLShaderLoader
{
public:
	GLVertexShaderLoader()
		: GLShaderLoader() { }

	GLVertexShaderLoader(const std::string& file_name)
		: GLShaderLoader(file_name)
	{
		this->Load();
	}

	void Load() override
	{
		int success;
		char info_log[1024];

		const char* source = this->source.c_str();

		this->id = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(this->GetId(), 1, &source, NULL);
		glCompileShader(this->GetId());

		glGetShaderiv(this->GetId(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->GetId(), 1024, NULL, info_log);
			std::cout << "GLVertexShader: Vertex Shader Compile Error" << std::endl;
			std::cout << info_log << std::endl;
		}
	}
};

class GLFragmentShaderLoader : public GLShaderLoader
{
public:
	GLFragmentShaderLoader() 
		: GLShaderLoader() { }

	GLFragmentShaderLoader(const std::string& file_name)
		: GLShaderLoader(file_name)
	{
		this->Load();
	}

	void Load() override
	{
		int success;
		char info_log[1024];

		const char* source = this->source.c_str();

		this->id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->GetId(), 1, &source, NULL);
		glCompileShader(this->GetId());

		glGetShaderiv(this->GetId(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->GetId(), 1024, NULL, info_log);
			std::cout << "GLFragmentShader: Fragment Shader Compile Error" << std::endl;
			std::cout << info_log << std::endl;
		}
	}
};


class GLShader
{
public:
	static std::shared_ptr<GLShader> GetDefaultShader()
	{
		static std::string vertex_source =
			"#version 330 core\n"
			"layout(location = 0) in vec4 in_Position;\n"
			"layout(location = 1) in vec4 in_Color;\n"
			"out vec4 out_Color;\n"
			"void main() {\n"
			"    gl_Position = in_Position;\n"
			"    out_Color = in_Color;\n"
			"}\n";

		static std::string fragment_source =
			"#version 330 core\n"
			"in vec4 out_Color;\n"
			"out vec4 fragColor;\n"
			"void main() {\n"
			"    fragColor = vec4(out_Color);\n"
			"}\n";

		GLVertexShaderLoader vertex_shader;
		vertex_shader.SetSource(vertex_source);
		vertex_shader.Load();

		GLFragmentShaderLoader fragment_shader;
		fragment_shader.SetSource(fragment_source);
		fragment_shader.Load();

		return std::make_shared<GLShader>(vertex_shader, fragment_shader);
	}
public:
	GLShader() 
		: id(-1) { }

	GLShader(GLVertexShaderLoader vertex_shader, GLFragmentShaderLoader fragment_shader)
	{
		this->CreateProgram(vertex_shader, fragment_shader);
	}

	GLShader(const std::string& vertex_file_name, const std::string& fragment_file_name)
	{
		this->Load(vertex_file_name, fragment_file_name);
	}

	~GLShader()
	{
		glDeleteProgram(this->id);
	}

	void Load(const std::string& vertex_file_name, const std::string& fragment_file_name)
	{
		GLVertexShaderLoader vertex_shader_loader(vertex_file_name);
		GLFragmentShaderLoader fragment_shader_loader(fragment_file_name);

		this->CreateProgram(vertex_shader_loader, fragment_shader_loader);
	}

	unsigned int GetId()
	{
		return this->id;
	}

	int GetUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(this->GetId(), name.c_str());
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

	void SetUniform(const std::string& name, glm::tvec2<int> value)
	{
		glUniform2i(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, glm::tvec3<int> value)
	{
		glUniform3i(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, glm::tvec4<int> value)
	{
		glUniform4i(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, unsigned int value)
	{
		glUniform1ui(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, glm::tvec2<unsigned int> value)
	{
		glUniform2ui(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, glm::tvec3<unsigned int> value)
	{
		glUniform3ui(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, glm::tvec4<unsigned int> value)
	{
		glUniform4ui(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, GLfloat value)
	{
		glUniform1f(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, glm::vec2 value)
	{
		glUniform2f(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, glm::vec3 value)
	{
		glUniform3f(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, glm::tvec4<GLfloat> value)
	{
		glUniform4f(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void SetUniform(const std::string& name, GLdouble value)
	{
		glUniform1d(this->GetUniformLocation(name.c_str()), value);
	}

	void SetUniform(const std::string& name, glm::tvec2<GLdouble> value)
	{
		glUniform2d(this->GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void SetUniform(const std::string& name, glm::tvec3<GLdouble> value)
	{
		glUniform3d(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void SetUniform(const std::string& name, glm::tvec4<GLdouble> value)
	{
		glUniform4d(this->GetUniformLocation(name.c_str()), value.x, value.y, value.z, value.w);
	}

	void Use()
	{
		glUseProgram(this->GetId());
	}

protected:
	void CreateProgram(GLVertexShaderLoader vertex_shader_loader, GLFragmentShaderLoader fragment_shader_loader)
	{
		int success;
		char info_log[1024];

		this->id = glCreateProgram();
		glAttachShader(this->id, vertex_shader_loader.GetId());
		glAttachShader(this->id, fragment_shader_loader.GetId());
		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 1024, NULL, info_log);
			std::cout << "GLShader: Program Linking Error" << std::endl;
			std::cout << info_log << std::endl;
		}

		glDeleteShader(vertex_shader_loader.GetId());
		glDeleteShader(fragment_shader_loader.GetId());
	}

private:
	unsigned int id;
};