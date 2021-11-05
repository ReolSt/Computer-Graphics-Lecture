#pragma once

#include "GLGameObject.h"
#include "GLPrimitiveMeshes.h"

class GLine : public GLGameObject
{
public:
	GConstructor(GLine, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineMesh>(color);
	}
};

class GAxis1D : public GLGameObject
{
public:
	GConstructor(GAxis1D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLAxis1DMesh>(color);
	}
};

class GAxis2D : public GLGameObject
{
public:
	GConstructor(GAxis2D,	const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLAxis2DMesh>(color);
	}
};

class GAxis3D : public GLGameObject
{
public:
	GConstructor(GAxis3D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLAxis3DMesh>(color);
	}
};

class GLineTriangle : public GLGameObject
{
public:
	GConstructor(GLineTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineTriangleMesh>(color);
	}
};

class GLineRectangle : public GLGameObject
{
public:
	GConstructor(GLineRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineRectangleMesh>(color);
	}
};

class GLineCircle : public GLGameObject
{
public:
	GConstructor(GLineCircle,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineCircleMesh>(vertices, color);
	}
};

class GLineCube : public GLGameObject
{
public:
	GConstructor(GLineCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineCubeMesh>(color);
	}
};

class GLineCone : public GLGameObject
{
public:
	GConstructor(GLineCone,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLLineConeMesh>(vertices, color);
	}
};

class GTriangle : public GLGameObject
{
public:
	GConstructor(GTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLTriangleMesh>(color);
	}
};

class GRectangle : public GLGameObject
{
public:
	GConstructor(GRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLRectangleMesh>(color);
	}
};

class GCircle : public GLGameObject
{
public:
	GConstructor(GCircle, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLCircleMesh>(vertices, color);
	}
};

class GCube : public GLGameObject
{
public:
	GConstructor(GCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLCubeMesh>(color);
	}
};

class GUVSphere : public GLGameObject
{
public:
	GConstructor(GUVSphere, unsigned int segments = 32, unsigned int rings = 16,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLUVSphereMesh>(segments, rings, color);
	}
};

class GIcoSphere : public GLGameObject
{
public:
	GConstructor(GIcoSphere, unsigned int subdivisions = 4,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLIcoSphereMesh>(subdivisions, color);
	}
};

class GCone : public GLGameObject
{
public:
	GConstructor(GCone, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLConeMesh>(vertices, color);
	}
};

class GCylinder : public GLGameObject
{
public:
	GConstructor(GCylinder, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->Mesh = GLCreate<GLCylinderMesh>(vertices, color);
	}
};