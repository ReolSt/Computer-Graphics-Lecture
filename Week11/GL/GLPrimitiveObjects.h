#pragma once

#include "GLBasicShader.h"
#include "GLGameObject.h"
#include "GLPrimitiveMeshes.h"

class GLine : public GLGameObject
{
public:
	GConstructor(GLine, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis1D : public GLGameObject
{
public:
	GConstructor(GAxis1D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLAxis1DMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis2D : public GLGameObject
{
public:
	GConstructor(GAxis2D,	const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLAxis2DMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis3D : public GLGameObject
{
public:
	GConstructor(GAxis3D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLAxis3DMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineTriangle : public GLGameObject
{
public:
	GConstructor(GLineTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineTriangleMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineRectangle : public GLGameObject
{
public:
	GConstructor(GLineRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineRectangleMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCircle : public GLGameObject
{
public:
	GConstructor(GLineCircle,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineCircleMesh>(vertices, color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCube : public GLGameObject
{
public:
	GConstructor(GLineCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineCubeMesh>(color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCone : public GLGameObject
{
public:
	GConstructor(GLineCone,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineConeMesh>(vertices, color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCylinder : public GLGameObject
{
public:
	GConstructor(GLineCylinder,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLLineCylinderMesh>(vertices, color));
		this->MeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GTriangle : public GLGameObject
{
public:
	GConstructor(GTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLTriangleMesh>(color));
	}
};

class GRectangle : public GLGameObject
{
public:
	GConstructor(GRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLRectangleMesh>(color));
	}
};

class GCircle : public GLGameObject
{
public:
	GConstructor(GCircle, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLCircleMesh>(vertices, color));
	}
};

class GCube : public GLGameObject
{
public:
	GConstructor(GCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLCubeMesh>(color));
	}
};

class GUVSphere : public GLGameObject
{
public:
	GConstructor(GUVSphere, unsigned int segments = 32, unsigned int rings = 16,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLUVSphereMesh>(segments, rings, color));
	}
};

class GIcoSphere : public GLGameObject
{
public:
	GConstructor(GIcoSphere, unsigned int subdivisions = 4,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLIcoSphereMesh>(subdivisions, color));
	}
};

class GCone : public GLGameObject
{
public:
	GConstructor(GCone, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLConeMesh>(vertices, color));
	}
};

class GCylinder : public GLGameObject
{
public:
	GConstructor(GCylinder, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		this->MeshRenderer->SetMesh(GLCreate<GLCylinderMesh>(vertices, color));
	}
};