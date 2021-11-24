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
		glm::vec3 v0(-0.5f, 0.0f, 0.0f);
		glm::vec3 v1(0.5f, 0.0f, 0.0f);

		this->AddVertices({ v0, v1 });
		this->AddColors({ color, color });

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
		glm::vec3 v0(-0.5f, 0.0f, 0.0f);
		glm::vec3 v1(0.5f, 0.0f, 0.0f);

		this->AddVertices({ v0, v1 });
		this->AddColors({ color, color });

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
		glm::vec3 v0(-0.5f, 0.0f, 0.0f);
		glm::vec3 v1(0.5f, 0.0f, 0.0f);
		glm::vec3 v2(0.0f, -0.5f, 0.0f);
		glm::vec3 v3(0.0f, 0.5f, 0.0f);

		this->AddVertices({ v0, v1, v2, v3 });
		this->AddColors({ color, color, color, color });

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
		glm::vec3 v0(-0.5f, 0.0f, 0.0f);
		glm::vec3 v1(0.5f, 0.0f, 0.0f);
		glm::vec3 v2(0.0f, -0.5f, 0.0f);
		glm::vec3 v3(0.0f, 0.5f, 0.0f);
		glm::vec3 v4(0.0f, 0.0f, -0.5f);
		glm::vec3 v5(0.0f, 0.0f, 0.5f);

		this->AddVertices({ v0, v1, v2, v3, v4, v5 });
		this->AddColors({ color, color, color, color, color, color });

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
		glm::vec3 v0(-0.5f, -0.5f, 0.0f);
		glm::vec3 v1(0.5f, -0.5f, 0.0f);
		glm::vec3 v2(0.0f, 0.5f, 0.0f);

		glm::vec3 normal(0.0f, 0.0f, 1.0f);

		this->AddVertices({ v0, v1, v2 });
		this->AddColors({ color, color, color });

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
		glm::vec3 v0(-0.5f, -0.5f, 0.0f);
		glm::vec3 v1(0.5f, -0.5f, 0.0f);
		glm::vec3 v2(-0.5f, 0.5f, 0.0f);
		glm::vec3 v3(0.5f, 0.5f, 0.0f);

		glm::vec3 normal(0.0f, 0.0f, 1.0f);

		this->AddVertices({ v0, v1, v2, v3 });
		this->AddColors({ color, color, color, color });

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

		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)(vertices));

			glm::vec3 v(glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f);

			this->AddVertex(v);
			this->AddColor(color);

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
		glm::vec3 v0(-0.5f, -0.5f, -0.5f);
		glm::vec3 v1(0.5f, -0.5f, -0.5f);
		glm::vec3 v2(-0.5f, 0.5f, -0.5f);
		glm::vec3 v3(0.5f, 0.5f, -0.5f);
		glm::vec3 v4(-0.5f, -0.5f, 0.5f);
		glm::vec3 v5(0.5f, -0.5f, 0.5f);
		glm::vec3 v6(-0.5f, 0.5f, 0.5f);
		glm::vec3 v7(0.5f, 0.5f, 0.5f);

		this->AddVertices({ v0, v1, v2, v3, v4, v5, v6, v7 });
		for (int i = 0; i < 8; ++i)
		{
			this->AddColor(color);
		}

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

		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		glm::vec3 top(0.0f, 0.5f, 0.0f);

		this->AddVertex(top);
		this->AddColor(color);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)vertices);

			glm::vec3 v(glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius);

			this->AddVertex(v);
			this->AddColor(color);

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

class GLLineCylinderMesh : public GLMesh
{
public:
	GLLineCylinderMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)vertices);

			glm::vec3 bottom({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius });
			glm::vec3 top({ glm::cos(rads) * radius, 0.5f, glm::sin(rads) * radius });

			this->AddVertices({ bottom, top });
			this->AddColors({ color, color });

			unsigned int next = (i + 1) % vertices;

			this->AddIndices({ 0, i * 2 });
			this->AddIndices({ i * 2 + 1, 1 });
			this->AddIndices({ i * 2, i * 2 + 1 });
			this->AddIndices({ i * 2, next * 2 });
			this->AddIndices({ i * 2 + 1, next * 2 + 1 });
		}

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
		glm::vec3 v0(-0.5f, -0.5f, 0.0f);
		glm::vec3 v1(0.5f, -0.5f, 0.0f);
		glm::vec3 v2(0.0f, 0.5f, 0.0f);

		glm::vec3 normal(0.0f, 0.0f, 1.0f);

		this->AddVertices({ v0, v1, v2 });

		for(int i = 0; i < 3; ++i)
		{
			this->AddColor(color);
			this->AddNormal(normal);
		}		

		this->AddIndices({ 0, 1, 2 });
	}
};

class GLRectangleMesh : public GL2DMesh
{
public:
	GLRectangleMesh(const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GL2DMesh()
	{
		glm::vec3 v0(-0.5f, -0.5f, 0.0f);
		glm::vec3 v1(0.5f, -0.5f, 0.0f);
		glm::vec3 v2(-0.5f, 0.5f, 0.0f);
		glm::vec3 v3(0.5f, 0.5f, 0.0f);

		glm::vec3 normal(0.0f, 0.0f, 1.0f);

		this->AddVertices({ v0, v1, v2, v3 });

		for (int i = 0; i < 4; ++i)
		{
			this->AddColor(color);
			this->AddNormal(normal);
		}

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

		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		glm::vec3 normal(0.0f, 0.0f, 1.0f);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)(vertices));

			glm::vec3 v({ glm::cos(rads) * radius, glm::sin(rads) * radius, 0.0f });

			this->AddVertex(v);
			this->AddColor(color);
			this->AddNormal(normal);

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
		glm::vec3 v0(-0.5f, -0.5f, -0.5f);
		glm::vec3 v1(0.5f, -0.5f, -0.5f);
		glm::vec3 v2(-0.5f, 0.5f, -0.5f);
		glm::vec3 v3(0.5f, 0.5f, -0.5f);
		glm::vec3 v4(-0.5f, -0.5f, 0.5f);
		glm::vec3 v5(0.5f, -0.5f, 0.5f);
		glm::vec3 v6(-0.5f, 0.5f, 0.5f);
		glm::vec3 v7(0.5f, 0.5f, 0.5f);

		this->AddVertices({ v0, v1, v2, v3, v4, v5, v6, v7 });
		this->AddColors({ color, color, color, color, color, color, color, color });

		std::array<glm::vec3, 8> vertexNormals;
		for (int i = 0; i < 8; ++i)
		{
			vertexNormals[i] = glm::vec3(0.0f);
		}

		std::array<glm::vec3, 6> surfaceNormals =
		{
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f)
		};

		int surfaceVertices[6][4] =
		{
			{1, 3, 5, 7},
			{0, 2, 4, 6},
			{2, 3, 6, 7},
			{0, 1, 4, 5},
			{4, 5, 6 ,7},
			{0, 1, 2, 3}
		};

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				vertexNormals[surfaceVertices[i][j]] += surfaceNormals[i];
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			this->AddNormal(glm::normalize(vertexNormals[i]));
		}

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

		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		std::vector<glm::vec3> vertexNormals(segments * rings + 2, glm::vec3(0.0f));

		vertexNormals[segments * rings] = glm::vec3(0.0f, -1.0f, 0.0f);
		vertexNormals[segments * rings + 1] = glm::vec3(0.0f, 1.0f, 0.0f);

		for (unsigned int r = 0; r < rings; ++r)
		{
			float ringRads = glm::mix(0.0f, pi, (r + 1) / (float)(rings + 1));

			float ringRadius = glm::sin(ringRads) * radius;
			float ringY = glm::cos(ringRads) * radius;

			unsigned int indexOffset = r * segments;
			unsigned int nextIndexOffset = (r + 1) * segments;

			for (unsigned int s = 0; s < segments; ++s)
			{
				float rads = glm::mix(0.0f, pi * 2, s / (float)segments);

				glm::vec3 v(glm::cos(rads) * ringRadius, ringY, glm::sin(rads) * ringRadius);

				this->AddVertex(v);
				this->AddColor(color);

				unsigned int nextSegment = (s + 1) % segments;

				vertexNormals[indexOffset + s] += normalize(v);

				if (r < rings - 1)
				{
					this->AddIndices({ indexOffset + s, indexOffset + nextSegment, nextIndexOffset + s });
					this->AddIndices({ nextIndexOffset + s, indexOffset + nextSegment, nextIndexOffset + nextSegment });
				}
			}
		}

		glm::vec3 bottom({ 0.0f, -0.5f, 0.0f });
		glm::vec3 top({ 0.0f, 0.5f, 0.0f });

		unsigned int indexOffset = this->GetVertexCount();

		this->AddVertices({ bottom, top });
		this->AddColors({ color, color });

		for (unsigned int segment = 0; segment < segments; ++segment)
		{
			this->AddIndices({ indexOffset - segment - 1, indexOffset, indexOffset - (segment + 1) % segments - 1 });
			this->AddIndices({ segment, indexOffset + 1, (segment + 1) % segments });
		}

		for (int i = 0; i < vertexNormals.size(); ++i)
		{
			this->AddNormal(glm::normalize(vertexNormals[i]));
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

		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		glm::vec3 top(0.0f, 0.5f, 0.0f);

		this->AddVertex(top);
		this->AddColor(color);

		glm::vec3 bottomNormal(0.0f, -1.0f, 0.0f);

		std::vector<glm::vec3> vertexNormals(vertices + 1, glm::vec3(0.0f));
		vertexNormals[0] = glm::vec3(0.0f, 1.0f, 0.0f);

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)vertices);

			glm::vec3 v({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius });

			this->AddVertex(v);
			this->AddColor(color);

			vertexNormals[i + 1] += bottomNormal;

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

		int offset = 1;
		for (int i = 0; i < vertices; ++i)
		{
			int next = (i + 1) % vertices;

			glm::vec3 v1 = this->GetVertex(i + offset) - top;
			glm::vec3 v2 = this->GetVertex(next + offset) - top;

			glm::vec3 normal = -glm::normalize(glm::cross(v1, v2));

			vertexNormals[i + offset] += normal;
			vertexNormals[next + offset] += normal;
		}

		for (int i = 0; i < vertexNormals.size(); ++i)
		{
			this->AddNormal(glm::normalize(vertexNormals[i]));
		}
	}
};

class GLCylinderMesh : public GLMesh
{
public:
	GLCylinderMesh(unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GLMesh()
	{
		constexpr float pi = glm::pi<float>();
		float radius = 0.5f;

		glm::vec3 topNormal(0.0f, 1.0f, 0.0f);
		glm::vec3 bottomNormal(0.0f, -1.0f, 0.0f);

		std::vector<glm::vec3> vertexNormals(vertices * 2, glm::vec3(0.0f));
		vertexNormals[0] = topNormal;
		vertexNormals[1] = bottomNormal;

		for (unsigned int i = 0; i < vertices; ++i)
		{
			float rads = glm::mix(0.0f, pi * 2, i / (float)vertices);

			glm::vec3 bottom({ glm::cos(rads) * radius, -0.5f, glm::sin(rads) * radius });
			glm::vec3 top({ glm::cos(rads) * radius, 0.5f, glm::sin(rads) * radius });

			float normalRads = glm::mix(0.0f, pi * 2, (i + 0.5f) / (float)vertices);
			glm::vec3 sideNormal(glm::cos(normalRads), 0.0f, glm::sin(normalRads));

			this->AddVertices({ bottom, top });
			this->AddColors({ color, color });

			unsigned int next = (i + 1) % vertices;

			vertexNormals[i * 2] += topNormal;
			vertexNormals[i * 2 + 1] += bottomNormal;

			vertexNormals[i * 2] += sideNormal;
			vertexNormals[i * 2 + 1] += sideNormal;
			vertexNormals[next * 2] += sideNormal;
			vertexNormals[next * 2 + 1] += sideNormal;

			this->AddIndices({ 0, i * 2, next * 2 });
			this->AddIndices({ next * 2 + 1, i * 2 + 1, 1 });
			this->AddIndices({ i * 2, i * 2 + 1, next * 2 });
			this->AddIndices({ next * 2 + 1, next * 2, i * 2 + 1 });
		}

		for (int i = 0; i < vertexNormals.size(); ++i)
		{
		    this->AddNormal(glm::normalize(vertexNormals[i]));
		}
	}
};