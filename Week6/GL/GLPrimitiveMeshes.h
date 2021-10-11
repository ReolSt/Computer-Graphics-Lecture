#pragma once

#include "GLMesh.h"

#include "GLColor.h"
#include "GLPoint.h"

class GLLineMesh : public GLMesh
{
public:
	GLLineMesh()
		: GLMesh() { }

protected:
	void Draw() override
	{
		if (this->indices.size() > 0)
		{
			glDrawElements(GL_LINES, this->indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
	}
};

class GLAxis1DMesh : public GLLineMesh
{
public:
	GLAxis1DMesh()
		: GLLineMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, white);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1 });

		this->indices.insert(this->indices.end(), { 0, 1 });
	}
};

class GLAxis2DMesh : public GLLineMesh
{
public:
	GLAxis2DMesh()
		: GLLineMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, white);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, white);
		GLPoint v2({ 0.0f, -0.5f, 0.0f }, white);
		GLPoint v3({ 0.0f, 0.5f, 0.0f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1, v2, v3 });

		this->indices.insert(this->indices.end(), { 0, 1, 2, 3 });
	}
};

class GLAxis3DMesh : public GLLineMesh
{
public:
	GLAxis3DMesh()
		: GLLineMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, white);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, white);
		GLPoint v2({ 0.0f, -0.5f, 0.0f }, white);
		GLPoint v3({ 0.0f, 0.5f, 0.0f }, white);
		GLPoint v4({ 0.0f, 0.0f, -0.5f }, white);
		GLPoint v5({ 0.0f, 0.0f, 0.5f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1, v2, v3, v4, v5 });

		this->indices.insert(this->indices.end(), { 0, 1, 2, 3, 4, 5 });
	}
};


class GLTriangleMesh : public GLMesh
{
public:
	GLTriangleMesh()
		: GLMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, white);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, white);
		GLPoint v2({ 0.0f, 0.5f, 0.0f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1, v2 });

		this->indices.insert(this->indices.end(), { 0, 1, 2 });
	}
};

class GLRectangleMesh : public GLMesh
{
public:
	GLRectangleMesh()
		: GLMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, white);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, white);
		GLPoint v2({ -0.5f, 0.5f, 0.0f }, white);
		GLPoint v3({ 0.5f, 0.5f, 0.0f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1, v2, v3 });

		this->indices.insert(this->indices.end(), { 0, 1, 2 });
		this->indices.insert(this->indices.end(), { 1, 2, 3 });
	}
};

class GLCircleMesh : public GLMesh
{
public:
	GLCircleMesh(unsigned int vertices = 32)
		: GLMesh()
	{
		assert(vertices >= 3);

		GLColor white(1.0f, 1.0f, 1.0f);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)(vertices));

			GLPoint v({ glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f }, white);

			this->vertices.push_back(v);
			if (i > 1)
			{
				this->indices.insert(this->indices.end(), { 0, i - 1, i });
			}
		}
	}
};

class GLCubeMesh : public GLMesh
{
public:
	GLCubeMesh()
		: GLMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLPoint v0({ -0.5f, -0.5f, -0.5f }, white);
		GLPoint v1({ 0.5f, -0.5f, -0.5f }, white);
		GLPoint v2({ -0.5f, 0.5f, -0.5f }, white);
		GLPoint v3({ 0.5f, 0.5f, -0.5f }, white);
		GLPoint v4({ -0.5f, -0.5f, 0.5f }, white);
		GLPoint v5({ 0.5f, -0.5f, 0.5f }, white);
		GLPoint v6({ -0.5f, 0.5f, 0.5f }, white);
		GLPoint v7({ 0.5f, 0.5f, 0.5f }, white);

		this->vertices.insert(this->vertices.end(), { v0, v1, v2, v3, v4, v5, v6, v7 });

		this->indices.insert(this->indices.end(), { 0, 1, 2 });
		this->indices.insert(this->indices.end(), { 1, 2, 3 });
		this->indices.insert(this->indices.end(), { 4, 5, 6 });
		this->indices.insert(this->indices.end(), { 5, 6, 7 });
		this->indices.insert(this->indices.end(), { 0, 2, 4 });
		this->indices.insert(this->indices.end(), { 2, 4, 6 });
		this->indices.insert(this->indices.end(), { 1, 3, 5 });
		this->indices.insert(this->indices.end(), { 3, 5, 7 });
		this->indices.insert(this->indices.end(), { 0, 1, 4 });
		this->indices.insert(this->indices.end(), { 1, 4, 5 });
		this->indices.insert(this->indices.end(), { 2, 3, 6 });
		this->indices.insert(this->indices.end(), { 3, 6, 7 });
	}
};

class GLUVSphereMesh : public GLMesh
{
public:
	GLUVSphereMesh(unsigned int segments = 32, unsigned int rings = 16)
		: GLMesh()
	{
		assert(segments >= 3 && rings >= 3);

		GLColor white(1.0f, 1.0f, 1.0f);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int r = 0; r < rings; ++r)
		{
			GLfloat rads = glm::mix(0.0f, pi, (r + 1) / (GLfloat)(rings + 1));

			GLfloat ring_radius = glm::sin(rads) * radius;
			GLfloat ring_y = glm::cos(rads) * radius;

			unsigned int index_offset = r * segments;
			unsigned int next_index_offset = (r + 1) * segments;

			for (unsigned int s = 0; s < segments; ++s)
			{
				GLfloat rads = glm::mix(0.0f, pi * 2, s / (GLfloat)segments);

				GLPoint v({ glm::cos(rads) * ring_radius, ring_y, glm::sin(rads) * ring_radius }, white);

				this->vertices.push_back(v);

				unsigned int next_s = (s + 1) % segments;

				if (r < rings - 1)
				{
					this->indices.insert(this->indices.end(), { index_offset + s, index_offset + next_s, next_index_offset + s });
					this->indices.insert(this->indices.end(), { index_offset + next_s, next_index_offset + s, next_index_offset + next_s });
				}
			}
		}

		GLPoint bottom({ 0.0f, -0.5f, 0.0f }, white);
		GLPoint top({ 0.0f, 0.5f, 0.0f }, white);

		unsigned int index_offset = this->vertices.size();

		this->vertices.insert(this->vertices.end(), { bottom, top });

		for (unsigned int s = 0; s < segments; ++s)
		{
			this->indices.insert(this->indices.end(), { index_offset, index_offset - s - 1, index_offset - (s + 1) % segments - 1 });
			this->indices.insert(this->indices.end(), { index_offset + 1, s, (s + 1) % segments });
		}
	}
};

class GLIcoSphereMesh : public GLMesh
{
public:
	GLIcoSphereMesh(unsigned int subdivisions = 4)
		: GLMesh()
	{

	}
};

class GLConeMesh : public GLMesh
{
public:
	GLConeMesh(unsigned int vertices = 32)
		: GLMesh()
	{
		assert(vertices >= 3);

		GLColor white(1.0f, 1.0f, 1.0f);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		GLPoint top({ 0.0f, 0.5f, 0.0f }, white);

		this->vertices.push_back(top);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, white);

			this->vertices.push_back(v);

			if (i > 0)
			{
				this->indices.insert(this->indices.end(), { 0, i, i + 1 });
			}
			if (i > 1)
			{
			    this->indices.insert(this->indices.end(), { 1, i, i + 1 });
			}
		}
		this->indices.insert(this->indices.end(), { 0, 1, vertices });
	}
};

class GLCylinderMesh : public GLMesh
{
public:
	GLCylinderMesh(unsigned int vertices = 32)
		: GLMesh()
	{
		GLColor white(1.0f, 1.0f, 1.0f);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint vBottom({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, white);
			GLPoint vTop({ glm::cos(rads) * radius, 0.5f, glm::sin(rads) * radius }, white);

			this->vertices.insert(this->vertices.end(), { vBottom, vTop });

			unsigned int next = (i + 1) % vertices;

			this->indices.insert(this->indices.end(), { 0, i * 2, next * 2 });
			this->indices.insert(this->indices.end(), { 1, i * 2 + 1, next * 2 + 1 });
			this->indices.insert(this->indices.end(), { i * 2, i * 2 + 1, next * 2 });
			this->indices.insert(this->indices.end(), { i * 2 + 1, next * 2, next * 2 + 1});
		}
	}
};