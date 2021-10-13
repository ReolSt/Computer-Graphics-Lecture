#pragma once

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtx/transform.hpp>
#include <gl/glm/gtx/quaternion.hpp>

#include "GLPoint.h"
#include "GLIndex.h"

class GLMesh
{
public:
	static const GLsizei VERTEX_DATA_SIZE = 4 * sizeof(GLfloat);
	static const GLsizei COLOR_DATA_SIZE = 4 * sizeof(GLfloat);
	static const GLsizei INDEX_DATA_SIZE = 1 * sizeof(GLuint);
public:
	GLMesh()
	{
		glGenVertexArrays(1, &this->vertex_array_id);

		glGenBuffers(1, &this->vertex_buffer_id);
		glGenBuffers(1, &this->color_buffer_id);
		glGenBuffers(1, &this->index_buffer_id);
	}

	virtual ~GLMesh()
	{

		glDeleteBuffers(1, &this->vertex_buffer_id);
		glDeleteBuffers(1, &this->color_buffer_id);
		glDeleteBuffers(1, &this->index_buffer_id);

		glDeleteVertexArrays(1, &this->vertex_array_id);
	}

	void Render()
	{
		glBindVertexArray(this->vertex_array_id);

		GLsizei vertex_buffer_size = VERTEX_DATA_SIZE * this->vertices.size();

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, NULL, GL_STATIC_DRAW);

		GLintptr vertex_buffer_offset = 0;

		for (const auto& vertex : this->vertices)
		{
			auto v = glm::vec4(vertex.position, 1.0f);

			GLfloat data[4] = { v.x, v.y, v.z, v.w };

			glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_offset, VERTEX_DATA_SIZE, data);
			vertex_buffer_offset += VERTEX_DATA_SIZE;
		}

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLsizei color_buffer_size = COLOR_DATA_SIZE * this->vertices.size();

		glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, color_buffer_size, NULL, GL_STATIC_DRAW);

		GLsizei color_buffer_offset = 0;

		for (const auto& vertex : this->vertices)
		{
			auto& color = vertex.color;
			GLfloat data[4] = { color.r, color.g, color.b, color.a };

			glBufferSubData(GL_ARRAY_BUFFER, color_buffer_offset, COLOR_DATA_SIZE, data);
			color_buffer_offset += COLOR_DATA_SIZE;
		}

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		GLsizei index_buffer_size = INDEX_DATA_SIZE * this->indices.size();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, NULL, GL_STATIC_DRAW);

		GLsizei index_buffer_offset = 0;

		for (const auto& index : this->indices)
		{
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_offset, INDEX_DATA_SIZE, &index);
			index_buffer_offset += INDEX_DATA_SIZE;
		}

		this->Draw();

		glBindVertexArray(0);
	}

	std::vector<GLPoint> vertices;
	std::vector<GLuint> indices;

protected:
	virtual void Draw()
	{
		if (this->indices.size() > 0)
		{
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
	}

private:
	unsigned int vertex_array_id;
	unsigned int vertex_buffer_id;
	unsigned int color_buffer_id;
	unsigned int index_buffer_id;
};