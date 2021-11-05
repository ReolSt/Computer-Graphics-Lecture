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

		this->AddVertices({ v0, v1 });
		this->AddIndices({ 0, 1 });

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

		this->AddVertices({ v0, v1 });
		this->AddIndices({ 0, 1 });

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

		this->AddVertices({ v0, v1, v2, v3 });
		this->AddIndices({ 0, 1, 2, 3 });

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

		this->AddVertices({ v0, v1, v2, v3, v4, v5 });
		this->AddIndices({ 0, 1, 2, 3, 4, 5 });

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

		this->AddVertices({ v0, v1, v2 });
		this->AddIndices({ 0, 1, 1, 2, 2, 0 });

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

		this->AddVertices({ v0, v1, v2, v3 });

		this->AddIndices({ 0, 1, 1, 3, 3, 2, 2, 0 });

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

			this->AddVertex(v);
			this->AddIndices({ i, (i + 1) % vertices });
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

		this->AddVertices({ v0, v1, v2, v3, v4, v5, v6, v7 });

		this->AddIndices({ 0, 1, 1, 3, 3, 2, 2, 0 });
		this->AddIndices({ 4, 5, 5, 7, 7, 6, 6, 4 });
		this->AddIndices({ 0, 2, 2, 6, 6, 4, 4, 0 });
		this->AddIndices({ 1, 3, 3, 7, 7, 5, 5, 1 });
		this->AddIndices({ 0, 1, 1, 5, 5, 4, 4, 0 });
		this->AddIndices({ 2, 3, 3, 7, 7, 6, 6, 2 });

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

		this->AddVertex(top);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, color);

			this->AddVertex(v);

			if (i > 0)
			{
				this->AddIndices({ 0, i + 1 });
			}
			if (i > 1)
			{
				this->AddIndices({ i, i + 1 });
			}
		}
		this->AddIndices({ 1, vertices });

		this->SetDrawMode(GLMeshDrawMode::Line);
	}
};

class GL2DMesh : public GLMesh
{
public:
	GL2DMesh()
		: GLMesh()
	{

	}

	void Render() override
	{
		bool faceCullingEnabled = glIsEnabled(GL_CULL_FACE);

		glDisable(GL_CULL_FACE);

		GLMesh::Render();

		if (faceCullingEnabled)
		{
			glEnable(GL_CULL_FACE);
		}
	}
};

class GLTriangleMesh : public GL2DMesh
{
public:
	GLTriangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GL2DMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ 0.0f, 0.5f, 0.0f }, color);

		this->AddVertices({ v0, v1, v2 });

		this->AddIndices({ 0, 1, 2 });
	}
};

class GLRectangleMesh : public GL2DMesh
{
public:
	GLRectangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GL2DMesh()
	{
		GLPoint v0({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint v1({ 0.5f, -0.5f, 0.0f }, color);
		GLPoint v2({ -0.5f, 0.5f, 0.0f }, color);
		GLPoint v3({ 0.5f, 0.5f, 0.0f }, color);

		this->AddVertices({ v0, v1, v2, v3 });

		this->AddIndices({ 0, 1, 2 });
		this->AddIndices({ 1, 3, 2 });
	}
};

class GLCircleMesh : public GL2DMesh
{
public:
	GLCircleMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GL2DMesh()
	{
		assert(vertices >= 3);

		constexpr GLfloat pi = glm::pi<GLfloat>();
		GLfloat radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)(vertices));

			GLPoint v({ glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f }, color);

			this->AddVertex(v);
			if (i > 1)
			{
				this->AddIndices({ 0, i - 1, i });
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

		this->AddVertices({ v0, v1, v2, v3, v4, v5, v6, v7 });

		this->AddIndices({ 2, 1, 0 });
		this->AddIndices({ 1, 2, 3 });
		this->AddIndices({ 4, 5, 6 });
		this->AddIndices({ 7, 6, 5 });
		this->AddIndices({ 4, 2, 0 });
		this->AddIndices({ 2, 4, 6 });
		this->AddIndices({ 1, 3, 5 });
		this->AddIndices({ 7, 5, 3 });
		this->AddIndices({ 0, 1, 4 });
		this->AddIndices({ 5, 4, 1 });
		this->AddIndices({ 6, 3, 2 });
		this->AddIndices({ 3, 6, 7 });
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

				this->AddVertex(v);

				unsigned int nextSegment = (segment + 1) % segments;

				if (ring < rings - 1)
				{
					this->AddIndices({ indexOffset + segment, indexOffset + nextSegment, nextIndexOffset + segment });
					this->AddIndices({ nextIndexOffset + segment, indexOffset + nextSegment, nextIndexOffset + nextSegment });
				}
			}
		}

		GLPoint bottom({ 0.0f, -0.5f, 0.0f }, color);
		GLPoint top({ 0.0f, 0.5f, 0.0f }, color);

		unsigned int indexOffset = this->Vertices.size();

		this->AddVertices({ bottom, top });

		for (unsigned int segment = 0; segment < segments; ++segment)
		{
			this->AddIndices({ indexOffset - segment - 1, indexOffset, indexOffset - (segment + 1) % segments - 1 });
			this->AddIndices({ segment, indexOffset + 1, (segment + 1) % segments });
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

		this->AddVertex(top);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			GLfloat rads = glm::mix(0.0f, pi * 2, i / (GLfloat)vertices);

			GLPoint v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius }, color);

			this->AddVertex(v);

			if (i > 0)
			{
				this->AddIndices({ i, 0, i + 1 });
			}
			if (i > 1)
			{
			    this->AddIndices({ 1, i, i + 1 });
			}
		}
		this->AddIndices({ 0, 1, vertices });
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

			this->AddVertices({ bottom, top });

			unsigned int next = (i + 1) % vertices;

			this->AddIndices({ 0, i * 2, next * 2 });
			this->AddIndices({ next * 2 + 1, i * 2 + 1, 1 });
			this->AddIndices({ i * 2, i * 2 + 1, next * 2 });
			this->AddIndices({ next * 2 + 1, next * 2, i * 2 + 1 });
		}
	}
};