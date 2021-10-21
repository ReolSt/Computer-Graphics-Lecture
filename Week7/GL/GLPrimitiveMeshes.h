#pragma once

#include "GLColor.h"
#include "GLPoint.h"
#include "GLMesh.h"

class GLLineMesh : public GLMesh
{
public:
	GLLineMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, color);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1 });
		this->Indices.insert(this->Indices.end(), { 0, 1 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLAxis1DMesh : public GLMesh
{
public:
	GLAxis1DMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, color);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1 });
		this->Indices.insert(this->Indices.end(), { 0, 1 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLAxis2DMesh : public GLMesh
{
public:
	GLAxis2DMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, color);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, color);
		GLPoint v2({ 0.0f, -0.5f, 0.0f }, color);
		GLPoint v3({ 0.0f, 0.5f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3 });
		this->Indices.insert(this->Indices.end(), { 0, 1, 2, 3 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLAxis3DMesh : public GLMesh
{
public:
	GLAxis3DMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, 0.0f, 0.0f }, color);
		GLPoint v1({ 0.5f, 0.0f, 0.0f }, color);
		GLPoint v2({ 0.0f, -0.5f, 0.0f }, color);
		GLPoint v3({ 0.0f, 0.5f, 0.0f }, color);
		GLPoint v4({ 0.0f, 0.0f, -0.5f }, color);
		GLPoint v5({ 0.0f, 0.0f, 0.5f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3, v4, v5 });
		this->Indices.insert(this->Indices.end(), { 0, 1, 2, 3, 4, 5 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLLineTriangleMesh : public GLMesh
{
public:
	GLLineTriangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ 0.0f, 0.5f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2 });
		this->Indices.insert(this->Indices.end(), { 0, 1, 1, 2, 2, 0 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLLineRectangleMesh : public GLMesh
{
public:
	GLLineRectangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ -0.5f, 0.5f, 0.0f }, color);
		GLPoint v3({ 0.5f, 0.5f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3 });

		this->Indices.insert(this->Indices.end(), { 0, 1, 1, 2, 2, 3, 3, 0 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLLineCircleMesh : public GLMesh
{
public:
	GLLineCircleMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		assert(vertices >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)(vertices));

			GLPoint v({ glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f }, color);

			this->Vertices.push_back(v);
			this->Indices.insert(this->Indices.end(), { i, (i + 1) % vertices });
		}

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLLineCubeMesh : public GLMesh
{
public:
	GLLineCubeMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, -0.5f }, color);
		GLPoint v1({ 0.5f, -0.5f, -0.5f }, color);
		GLPoint v2({ -0.5f, 0.5f, -0.5f }, color);
		GLPoint v3({ 0.5f, 0.5f, -0.5f }, color);
		GLPoint v4({ -0.5f, -0.5f, 0.5f }, color);
		GLPoint v5({ 0.5f, -0.5f, 0.5f }, color);
		GLPoint v6({ -0.5f, 0.5f, 0.5f }, color);
		GLPoint v7({ 0.5f, 0.5f, 0.5f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3, v4, v5, v6, v7 });

		this->Indices.insert(this->Indices.end(), { 0, 1, 1, 3, 3, 2, 2, 0 });
		this->Indices.insert(this->Indices.end(), { 4, 5, 5, 7, 7, 6, 6, 4 });
		this->Indices.insert(this->Indices.end(), { 0, 2, 2, 6, 6, 4, 4, 0 });
		this->Indices.insert(this->Indices.end(), { 1, 3, 3, 7, 7, 5, 5, 1 });
		this->Indices.insert(this->Indices.end(), { 0, 1, 1, 5, 5, 4, 4, 0 });
		this->Indices.insert(this->Indices.end(), { 2, 3, 3, 7, 7, 6, 6, 2 });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLLineConeMesh : public GLMesh
{
public:
	GLLineConeMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		assert(vertices >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		GLPoint top({ 0.0f, 0.5f, 0.0f }, color);

		this->Vertices.push_back(top);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, color);

			this->Vertices.push_back(v);

			if (i > 0)
			{
				this->Indices.insert(this->Indices.end(), { 0, i + 1 });
			}
			if (i > 1)
			{
				this->Indices.insert(this->Indices.end(), { i, i + 1 });
			}
		}
		this->Indices.insert(this->Indices.end(), { 1, vertices });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GLTriangleMesh : public GLMesh
{
public:
	GLTriangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ 0.0f, 0.5f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2 });

		this->Indices.insert(this->Indices.end(), { 0, 1, 2 });
	}
};

class GLRectangleMesh : public GLMesh
{
public:
	GLRectangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ -0.5f, 0.5f, 0.0f }, color);
		GLPoint v3({ 0.5f, 0.5f, 0.0f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3 });

		this->Indices.insert(this->Indices.end(), { 0, 1, 2 });
		this->Indices.insert(this->Indices.end(), { 1, 3, 2 });
	}
};

class GLCircleMesh : public GLMesh
{
public:
	GLCircleMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		assert(vertices >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)(vertices));

			GLPoint v({ glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f }, color);

			this->Vertices.push_back(v);
			if (i > 1)
			{
				this->Indices.insert(this->Indices.end(), { 0, i - 1, i });
			}
		}
	}
};

class GLCubeMesh : public GLMesh
{
public:
	GLCubeMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, -0.5f }, color);
		GLPoint v1({ 0.5f, -0.5f, -0.5f }, color);
		GLPoint v2({ -0.5f, 0.5f, -0.5f }, color);
		GLPoint v3({ 0.5f, 0.5f, -0.5f }, color);
		GLPoint v4({ -0.5f, -0.5f, 0.5f }, color);
		GLPoint v5({ 0.5f, -0.5f, 0.5f }, color);
		GLPoint v6({ -0.5f, 0.5f, 0.5f }, color);
		GLPoint v7({ 0.5f, 0.5f, 0.5f }, color);

		this->Vertices.insert(this->Vertices.end(), { v0, v1, v2, v3, v4, v5, v6, v7 });

		this->Indices.insert(this->Indices.end(), { 2, 1, 0 });
		this->Indices.insert(this->Indices.end(), { 1, 2, 3 });
		this->Indices.insert(this->Indices.end(), { 4, 5, 6 });
		this->Indices.insert(this->Indices.end(), { 7, 6, 5 });
		this->Indices.insert(this->Indices.end(), { 4, 2, 0 });
		this->Indices.insert(this->Indices.end(), { 2, 4, 6 });
		this->Indices.insert(this->Indices.end(), { 1, 3, 5 });
		this->Indices.insert(this->Indices.end(), { 7, 5, 3 });
		this->Indices.insert(this->Indices.end(), { 0, 1, 4 });
		this->Indices.insert(this->Indices.end(), { 5, 4, 1 });
		this->Indices.insert(this->Indices.end(), { 6, 3, 2 });
		this->Indices.insert(this->Indices.end(), { 3, 6, 7 });
	}
};

class GLUVSphereMesh : public GLMesh
{
public:
	GLUVSphereMesh(unsigned int segments = 32, unsigned int rings = 16, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		assert(segments >= 3 && rings >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int ring = 0; ring < rings; ++ring)
		{
			GLfloat rads = glm::mix(0.0f, pi, (ring + 1) / (GLfloat)(rings + 1));

			GLfloat ringRadius = glm::sin(rads) * radius;
			GLfloat ringY = glm::cos(rads) * radius;

			unsigned int indexOffset = ring * segments;
			unsigned int nextIndexOffset = (ring + 1) * segments;

			for (unsigned int segment = 0; segment < segments; ++segment)
			{
				GLfloat rads = glm::mix(0.0f, pi * 2, segment / (GLfloat)segments);

				GLPoint v({ glm::cos(rads) * ringRadius, ringY, glm::sin(rads) * ringRadius }, color);

				this->Vertices.push_back(v);

				unsigned int nextSegment = (segment + 1) % segments;

				if (ring < rings - 1)
				{
					this->Indices.insert(this->Indices.end(), { indexOffset + segment, indexOffset + nextSegment, nextIndexOffset + segment });
					this->Indices.insert(this->Indices.end(), { nextIndexOffset + segment, indexOffset + nextSegment, nextIndexOffset + nextSegment });
				}
			}
		}

		GLPoint bottom({ 0.0f, -0.5f, 0.0f }, color);
		GLPoint top({ 0.0f, 0.5f, 0.0f }, color);

		unsigned int indexOffset = this->Vertices.size();

		this->Vertices.insert(this->Vertices.end(), { bottom, top });

		for (unsigned int segment = 0; segment < segments; ++segment)
		{
			this->Indices.insert(this->Indices.end(), { indexOffset - segment - 1, indexOffset, indexOffset - (segment + 1) % segments - 1 });
			this->Indices.insert(this->Indices.end(), { segment, indexOffset + 1, (segment + 1) % segments });
		}
	}
};

class GLIcoSphereMesh : public GLMesh
{
public:
	GLIcoSphereMesh(unsigned int subdivisions = 4, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{

	}
};

class GLConeMesh : public GLMesh
{
public:
	GLConeMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		assert(vertices >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		GLPoint top({ 0.0f, 0.5f, 0.0f }, color);

		this->Vertices.push_back(top);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, color);

			this->Vertices.push_back(v);

			if (i > 0)
			{
				this->Indices.insert(this->Indices.end(), { i, 0, i + 1 });
			}
			if (i > 1)
			{
			    this->Indices.insert(this->Indices.end(), { 1, i, i + 1 });
			}
		}
		this->Indices.insert(this->Indices.end(), { 0, 1, vertices });
	}
};

class GLCylinderMesh : public GLMesh
{
public:
	GLCylinderMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint bottom({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, color);
			GLPoint top({ glm::cos(rads) * radius, 0.5f, glm::sin(rads) * radius }, color);

			this->Vertices.insert(this->Vertices.end(), { bottom, top });

			unsigned int next = (i + 1) % vertices;

			this->Indices.insert(this->Indices.end(), { 0, i * 2, next * 2 });
			this->Indices.insert(this->Indices.end(), { next * 2 + 1, i * 2 + 1, 1 });
			this->Indices.insert(this->Indices.end(), { i * 2, i * 2 + 1, next * 2 });
			this->Indices.insert(this->Indices.end(), { next * 2 + 1, next * 2, i * 2 + 1 });
		}
	}
};