#pragma once

#include <gl/glew.h>

#include "GLMemoryHelpers.h"
#include "GLPoint.h"

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
	static const GLsizei INDEX_DATA_SIZE = 1 * sizeof(GLuint);
public:
	GLMesh()
	{
		glGenVertexArrays(1, &this->VertexArrayId);

		glGenBuffers(1, &this->VertexBufferId);
		glGenBuffers(1, &this->ColorBufferId);
		glGenBuffers(1, &this->IndexBufferId);
	}

	virtual ~GLMesh()
	{

		glDeleteBuffers(1, &this->VertexBufferId);
		glDeleteBuffers(1, &this->ColorBufferId);
		glDeleteBuffers(1, &this->IndexBufferId);

		glDeleteVertexArrays(1, &this->VertexArrayId);
	}

	void Render()
	{
		glBindVertexArray(this->VertexArrayId);

		GLsizei VertexBufferSize = VERTEX_DATA_SIZE * this->Vertices.size();
		GLintptr VertexBufferOffset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, VertexBufferSize, NULL, GL_STATIC_DRAW);

		for (const auto& Vertex : this->Vertices)
		{
			auto VPosition = glm::vec4(Vertex.Position, 1.0f);

			GLfloat data[4] = { VPosition.x, VPosition.y, VPosition.z, VPosition.w };

			glBufferSubData(GL_ARRAY_BUFFER, VertexBufferOffset, VERTEX_DATA_SIZE, data);
			VertexBufferOffset += VERTEX_DATA_SIZE;
		}

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLsizei ColorBufferSize = COLOR_DATA_SIZE * this->Vertices.size();
		GLintptr ColorBufferOffset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, this->ColorBufferId);
		glBufferData(GL_ARRAY_BUFFER, ColorBufferSize, NULL, GL_STATIC_DRAW);

		for (const auto& Vertex : this->Vertices)
		{
			auto& VColor = Vertex.Color;
			GLfloat Data[4] = { VColor.r, VColor.g, VColor.b, VColor.a };

			glBufferSubData(GL_ARRAY_BUFFER, ColorBufferOffset, COLOR_DATA_SIZE, Data);
			ColorBufferOffset += COLOR_DATA_SIZE;
		}

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		GLsizei IndexBufferSIze = INDEX_DATA_SIZE * this->Indices.size();
		GLintptr IndexBufferOffset = 0;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferSIze, NULL, GL_STATIC_DRAW);

		for (const auto& Index : this->Indices)
		{
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferOffset, INDEX_DATA_SIZE, &Index);
			IndexBufferOffset += INDEX_DATA_SIZE;
		}

		this->Draw();

		glBindVertexArray(0);
	}

	void SetDrawMode(GLMeshDrawMode drawMode)
	{
		this->DrawMode = drawMode;
	}

	GLMeshDrawMode GetDrawMode()
	{
		return this->DrawMode;
	}

	std::vector<GLPoint> Vertices;
	std::vector<GLuint> Indices;

protected:
	virtual void Draw()
	{
		if (this->Indices.size() > 0)
		{
			glDrawElements((GLenum)this->DrawMode, this->Indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
	}

private:
	unsigned int VertexArrayId;
	unsigned int VertexBufferId;
	unsigned int ColorBufferId;
	unsigned int IndexBufferId;

	GLMeshDrawMode DrawMode = GLMeshDrawMode::Triangle;
};
