#pragma once

#include <gl/glew.h>

#include "GLMemoryHelpers.h"
#include "GLPoint.h"
#include "GLColor.h"

enum class GLMeshDrawMode
{
	Point = GL_POINTS,
	Line = GL_LINES,
	LineStrip = GL_LINE_STRIP,
	LineLoop = GL_LINE_LOOP,
	Triangle = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Quad = GL_QUADS,
	QuadStrip = GL_QUAD_STRIP,
	Polygon = GL_POLYGON
};

class GLMesh
{
public:
	static const GLsizei VERTEX_DATA_SIZE = 4 * sizeof(GLfloat);
	static const GLsizei COLOR_DATA_SIZE = 4 * sizeof(GLfloat);
	static const GLsizei NORMAL_DATA_SIZE = 4 * sizeof(GLfloat);
	static const GLsizei INDEX_DATA_SIZE = 1 * sizeof(GLuint);
public:
	GLMesh()
	{
		glGenVertexArrays(1, &this->vertexArrayId);

		glGenBuffers(1, &this->vertexBufferId);
		glGenBuffers(1, &this->colorBufferId);
		glGenBuffers(1, &this->normalBufferId);
		glGenBuffers(1, &this->indexBufferId);
	}

	virtual ~GLMesh()
	{

		glDeleteBuffers(1, &this->vertexBufferId);
		glDeleteBuffers(1, &this->colorBufferId);
		glDeleteBuffers(1, &this->normalBufferId);
		glDeleteBuffers(1, &this->indexBufferId);

		glDeleteVertexArrays(1, &this->vertexArrayId);
	}

	void UpdateVertexBuffer()
	{
		glBindVertexArray(this->vertexArrayId);

		GLsizei vertexBufferSize = VERTEX_DATA_SIZE * this->vertices.size();
		GLintptr vertexBufferOffset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_STATIC_DRAW);

		for (const auto& vertex : this->vertices)
		{
			auto vPosition = glm::vec4(vertex, 1.0f);

			GLfloat data[4] = { vPosition.x, vPosition.y, vPosition.z, vPosition.w };

			glBufferSubData(GL_ARRAY_BUFFER, vertexBufferOffset, VERTEX_DATA_SIZE, data);
			vertexBufferOffset += VERTEX_DATA_SIZE;
		}

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void UpdateColorBuffer()
	{
		glBindVertexArray(this->vertexArrayId);

		GLsizei colorBufferSize = COLOR_DATA_SIZE * this->vertices.size();
		GLintptr colorBufferOffset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferId);
		glBufferData(GL_ARRAY_BUFFER, colorBufferSize, NULL, GL_STATIC_DRAW);

		for (const auto& color : this->colors)
		{
			GLfloat data[4] = { color.r, color.g, color.b, color.a };

			glBufferSubData(GL_ARRAY_BUFFER, colorBufferOffset, COLOR_DATA_SIZE, data);
			colorBufferOffset += COLOR_DATA_SIZE;
		}

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void UpdateNormalBuffer()
	{
		glBindVertexArray(this->vertexArrayId);

		GLsizei normalBufferSize = NORMAL_DATA_SIZE * this->normals.size();
		GLintptr normalBufferOffset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, this->normalBufferId);
		glBufferData(GL_ARRAY_BUFFER, normalBufferSize, NULL, GL_STATIC_DRAW);

		for (const auto& normal : this->normals)
		{
			auto vNormal = glm::vec4(normal, 1.0f);

			GLfloat data[4] = { vNormal.x, vNormal.y, vNormal.z, vNormal.w };

			glBufferSubData(GL_ARRAY_BUFFER, normalBufferOffset, NORMAL_DATA_SIZE, data);
			normalBufferOffset += NORMAL_DATA_SIZE;
		}
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void UpdateIndexBuffer()
	{
		glBindVertexArray(this->vertexArrayId);

		GLsizei indexBufferSIze = INDEX_DATA_SIZE * this->indices.size();
		GLintptr indexBufferOffset = 0;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSIze, NULL, GL_STATIC_DRAW);

		for (const auto& index : this->indices)
		{
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexBufferOffset, INDEX_DATA_SIZE, &index);
			indexBufferOffset += INDEX_DATA_SIZE;
		}

		glBindVertexArray(0);
	}

	void Update()
	{
		this->UpdateVertexBuffer();
		this->UpdateColorBuffer();
		this->UpdateNormalBuffer();
		this->UpdateIndexBuffer();
	}

	virtual void Render()
	{
		if (this->updated)
		{
			this->Update();
			this->updated = false;
		}

		glBindVertexArray(this->vertexArrayId);

		if (this->indices.size() > 0)
		{
			glDrawElements((GLenum)this->drawMode, this->indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
		}

		glBindVertexArray(0);
	}

	void SetDrawMode(GLMeshDrawMode drawMode)
	{
		this->drawMode = drawMode;
	}

	GLMeshDrawMode GetDrawMode()
	{
		return this->drawMode;
	}


	glm::vec3 GetVertex(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->vertices.size());

		return this->vertices.at(arrayIndex);
	}

	std::vector<glm::vec3>& GetVertices()
	{
		return this->vertices;
	}

	void SetVertex(int arrayIndex, const glm::vec3& vertex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->vertices.size());

		this->vertices.at(arrayIndex) = vertex;

		this->updated = true;
	}

	void AddVertex(const glm::vec3& vertex)
	{
		this->vertices.push_back(vertex);

		this->updated = true;
	}

	void AddVertices(const std::initializer_list<glm::vec3>& vertices)
	{
		this->vertices.insert(this->vertices.end(), vertices);

		this->updated = true;
	}

	void RemoveVertex(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->vertices.size());

		this->vertices.erase(this->vertices.begin() + arrayIndex);

		this->updated = true;
	}

	void RemoveVertices(const std::initializer_list<int>& vertexIndices)
	{
		for (auto index : vertexIndices)
		{
			this->RemoveVertex(index);
		}

		this->updated = true;
	}

	void ClearVertices()
	{
		this->vertices.clear();

		this->updated = true;
	}

	size_t GetVertexCount()
	{
		return this->vertices.size();
	}

	GLColor GetColor(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->colors.size());

		return this->colors.at(arrayIndex);
	}

	std::vector<GLColor>& GetColors()
	{
		return this->colors;
	}

	void SetColor(int arrayIndex, const GLColor& color)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->colors.size());

		this->colors.at(arrayIndex) = color;

		this->updated = true;
	}

	void AddColor(const GLColor& color)
	{
		this->colors.push_back(color);

		this->updated = true;
	}

	void AddColors(const std::initializer_list<GLColor>& colors)
	{
		this->colors.insert(this->colors.end(), colors);

		this->updated = true;
	}

	void RemoveColor(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->colors.size());

		this->colors.erase(this->colors.begin() + arrayIndex);

		this->updated = true;
	}

	void RemoveColors(const std::initializer_list<int>& colorIndices)
	{
		for (auto index : colorIndices)
		{
			this->RemoveColor(index);
		}

		this->updated = true;
	}

	void ClearColors()
	{
		this->colors.clear();

		this->updated = true;
	}

	size_t GetColorCount()
	{
		return this->colors.size();
	}

	glm::vec3 GetNormal(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->normals.size());

		return this->normals.at(arrayIndex);
	}

	std::vector<glm::vec3>& GetNormals()
	{
		return this->normals;
	}

	glm::vec3 SetNormal(int arrayIndex, const glm::vec3& normal)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->normals.size());

		this->normals.at(arrayIndex) = normal;

		this->updated = true;
	}

	void AddNormal(const glm::vec3& normal)
	{
		this->normals.push_back(normal);

		this->updated = true;
	}

	void AddNormals(const std::initializer_list<glm::vec3>& normals)
	{
		this->normals.insert(this->normals.end(), normals);

		this->updated = true;
	}

	void RemoveNormal(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->normals.size());

		this->vertices.erase(this->vertices.begin() + arrayIndex);

		this->updated = true;
	}

	void RemoveNormals(const std::initializer_list<int>& normalIndices)
	{
		for (auto index : normalIndices)
		{
			this->RemoveNormal(index);
		}

		this->updated = true;
	}

	size_t GetNormalCount()
	{
		return this->normals.size();
	}

	void ClearNormals()
	{
		this->normals.clear();

		this->updated = true;
	}

	GLuint GetIndex(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->indices.size());

		return this->indices.at(arrayIndex);
	}

	std::vector<unsigned int>& GetIndices()
	{
		return this->indices;
	}

	size_t GetIndexCount()
	{
		return this->indices.size();
	}

	void SetIndex(int arrayIndex, GLuint index)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->indices.size());

		this->indices.at(arrayIndex) = index;

		this->updated = true;
	}

	void AddIndex(GLuint index)
	{
		this->indices.push_back(index);

		this->updated = true;
	}

	void AddIndices(const std::initializer_list<GLuint>& indices)
	{
		for (auto index : indices)
		{
			this->AddIndex(index);
		}

		this->updated = true;
	}

	void RemoveIndex(int arrayIndex)
	{
		assert(arrayIndex >= 0 && arrayIndex < this->indices.size());
		
		this->indices.erase(this->indices.begin() + arrayIndex);

		this->updated = true;
	}

	void ClearIndices()
	{
		this->indices.clear();

		this->updated = true;
	}

private:
	std::vector<glm::vec3> vertices;
	std::vector<GLColor> colors;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;

	unsigned int vertexArrayId;

	unsigned int vertexBufferId;
	unsigned int colorBufferId;
	unsigned int normalBufferId;
	unsigned int indexBufferId;

	GLMeshDrawMode drawMode = GLMeshDrawMode::Triangle;

	bool updated = false;
};
