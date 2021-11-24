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
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis1D : public GLGameObject
{
public:
	GConstructor(GAxis1D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLAxis1DMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis2D : public GLGameObject
{
public:
	GConstructor(GAxis2D,	const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLAxis2DMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GAxis3D : public GLGameObject
{
public:
	GConstructor(GAxis3D, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLAxis3DMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineTriangle : public GLGameObject
{
public:
	GConstructor(GLineTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineTriangleMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineRectangle : public GLGameObject
{
public:
	GConstructor(GLineRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineRectangleMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCircle : public GLGameObject
{
public:
	GConstructor(GLineCircle,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineCircleMesh>(vertices, color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCube : public GLGameObject
{
public:
	GConstructor(GLineCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineCubeMesh>(color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCone : public GLGameObject
{
public:
	GConstructor(GLineCone,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineConeMesh>(vertices, color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GLineCylinder : public GLGameObject
{
public:
	GConstructor(GLineCylinder,
		unsigned int vertices = 32, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLLineCylinderMesh>(vertices, color));
		meshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
	}
};

class GTriangle : public GLGameObject
{
public:
	GConstructor(GTriangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLTriangleMesh>(color));
	}
};

class GRectangle : public GLGameObject
{
public:
	GConstructor(GRectangle, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLRectangleMesh>(color));
	}
};

class GCircle : public GLGameObject
{
public:
	GConstructor(GCircle, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLCircleMesh>(vertices, color));
	}
};

class GCube : public GLGameObject
{
public:
	GConstructor(GCube, const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLCubeMesh>(color));
	}
};

class GUVSphere : public GLGameObject
{
public:
	GConstructor(GUVSphere, unsigned int segments = 32, unsigned int rings = 16,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLUVSphereMesh>(segments, rings, color));
	}
};

class GIcoSphere : public GLGameObject
{
public:
	GConstructor(GIcoSphere, unsigned int subdivisions = 4,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLIcoSphereMesh>(subdivisions, color));
	}
};

class GCone : public GLGameObject
{
public:
	GConstructor(GCone, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLConeMesh>(vertices, color));
	}
};

class GCylinder : public GLGameObject
{
public:
	GConstructor(GCylinder, unsigned int vertices = 32,
		const GLColor& color = GLColor(1.0f, 1.0f, 1.0f))
		: GSuperClassInitializer(GLGameObject)
	{
		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(GLCreate<GLCylinderMesh>(vertices, color));
	}
};