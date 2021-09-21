#pragma once

#include <mutex>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtx/transform.hpp>
#include <gl/glm/gtx/quaternion.hpp>

#include "GLPoint.h"
#include "GLLine.h"
#include "GLTriangle.h"
#include "GLTransform.h"

class GLMesh
{
public:
	static const GLsizei POINT_VERTEX_SIZE = 1 * 4 * sizeof(GLfloat);
	static const GLsizei POINT_COLOR_SIZE = 1 * 4 * sizeof(GLfloat);
	static const GLsizei LINE_VERTEX_SIZE = 2 * 4 * sizeof(GLfloat);
	static const GLsizei LINE_COLOR_SIZE = 2 * 4 * sizeof(GLfloat);
	static const GLsizei TRIANGLE_VERTEX_SIZE = 3 * 4 * sizeof(GLfloat);
	static const GLsizei TRIANGLE_COLOR_SIZE = 3 * 4 * sizeof(GLfloat);
public:
	GLMesh()
	{
		glGenVertexArrays(1, &this->vertex_array_id);

		glGenBuffers(1, &this->vertex_buffer_id);
		glGenBuffers(1, &this->color_buffer_id);
	}

	virtual ~GLMesh()
	{
		std::lock_guard<std::mutex> guard(this->rendering);

		glDeleteBuffers(1, &this->vertex_buffer_id);
		glDeleteBuffers(1, &this->color_buffer_id);

		glDeleteVertexArrays(1, &this->vertex_array_id);
	}

	void Render(GLTransform& transform)
	{
		std::lock_guard<std::mutex> guard(this->rendering);
		glBindVertexArray(this->vertex_array_id);

		GLsizei point_buffer_size = this->points.size();
		GLsizei line_buffer_size = this->lines.size();
		GLsizei triangle_buffer_size = this->triangles.size();

		GLsizei vertex_buffer_size =
			POINT_VERTEX_SIZE * point_buffer_size +
			LINE_VERTEX_SIZE * line_buffer_size +
			TRIANGLE_VERTEX_SIZE * triangle_buffer_size;

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, NULL, GL_STATIC_DRAW);

		GLintptr vertex_buffer_offset = 0;

		for (const auto& point : this->points)
		{
			auto position = GLTransform::ApplyTransform(transform, point.position);
			GLfloat data[4] = { position.x, position.y, position.z, position.w };

			glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_offset, POINT_VERTEX_SIZE, data);
			vertex_buffer_offset += POINT_VERTEX_SIZE;
		}

		for (const auto& line : this->lines)
		{
			auto v1 = GLTransform::ApplyTransform(transform, line.v1.position);
			auto v2 = GLTransform::ApplyTransform(transform, line.v2.position);
			GLfloat data[2][4] =
			{
				{ v1.x, v1.y, v1.z, v1.w },
				{ v2.x, v2.y, v2.z, v1.w }
			};

			glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_offset, LINE_VERTEX_SIZE, data);
			vertex_buffer_offset += LINE_VERTEX_SIZE;
		}

		for (const auto& triangle : this->triangles)
		{
			auto v1 = GLTransform::ApplyTransform(transform, triangle.v1.position);
			auto v2 = GLTransform::ApplyTransform(transform, triangle.v2.position);
			auto v3 = GLTransform::ApplyTransform(transform, triangle.v3.position);

			GLfloat data[3][4] =
			{
				{v1.x, v1.y, v1.z, v1.w},
				{v2.x, v2.y, v2.z, v2.w},
				{v3.x, v3.y, v3.z, v3.w}
			};

			glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_offset, TRIANGLE_VERTEX_SIZE, data);
			vertex_buffer_offset += TRIANGLE_VERTEX_SIZE;
		}

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLsizei color_buffer_size =
			POINT_COLOR_SIZE * point_buffer_size +
			LINE_COLOR_SIZE * line_buffer_size +
			TRIANGLE_COLOR_SIZE * triangle_buffer_size;

		glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, color_buffer_size, NULL, GL_STATIC_DRAW);

		GLsizei color_buffer_offset = 0;

		for (const auto& point : this->points)
		{
			auto& color = point.color;
			GLfloat data[4] = { color.r, color.g, color.b, color.a };

			glBufferSubData(GL_ARRAY_BUFFER, color_buffer_offset, POINT_COLOR_SIZE, data);
			color_buffer_offset += POINT_COLOR_SIZE;
		}

		for (const auto& line : this->lines)
		{
			auto& v1 = line.v1.color;
			auto& v2 = line.v2.color;
			GLfloat data[2][4] =
			{
				{ v1.r, v1.g, v1.b, v1.a },
				{ v2.r, v2.g, v2.b, v2.a }
			};

			glBufferSubData(GL_ARRAY_BUFFER, color_buffer_offset, LINE_COLOR_SIZE, data);
			color_buffer_offset += LINE_COLOR_SIZE;
		}

		for (const auto& triangle : this->triangles)
		{
			auto& v1 = triangle.v1.color;
			auto& v2 = triangle.v2.color;
			auto& v3 = triangle.v3.color;

			GLfloat data[3][4] =
			{
				{v1.r, v1.g, v1.b, v1.a},
				{v2.r, v2.g, v2.b, v2.a},
				{v3.r, v3.g, v3.b, v3.a}
			};

			glBufferSubData(GL_ARRAY_BUFFER, color_buffer_offset, TRIANGLE_COLOR_SIZE, data);
			color_buffer_offset += TRIANGLE_COLOR_SIZE;
		}

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		if (point_buffer_size > 0)
		{
			glDrawArrays(GL_POINTS, 0, point_buffer_size);
		}

		if (line_buffer_size > 0)
		{
			glDrawArrays(GL_LINES, point_buffer_size, line_buffer_size * 2);
		}

		if (triangle_buffer_size > 0)
		{
			glDrawArrays(GL_TRIANGLES, point_buffer_size + line_buffer_size * 2, triangle_buffer_size * 3);
		}

		glBindVertexArray(0);
	}

	std::vector<GLPoint> points;
	std::vector<GLLine> lines;
	std::vector<GLTriangle> triangles;
private:
	unsigned int vertex_array_id;
	unsigned int vertex_buffer_id;
	unsigned int color_buffer_id;

	std::mutex rendering;
};