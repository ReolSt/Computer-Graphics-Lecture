#pragma once

#include <cmath>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtx/transform.hpp>
#include <gl/glm/gtx/quaternion.hpp>
#include <gl/glm/gtx/string_cast.hpp>

#include "GLMemoryHelpers.h"

class GLGameObject;

class GLTransform
{
public:
	GLTransform(GLGameObject* gameObject)
	{
		this->GameObject = gameObject;
	}

	GLTransform(const GLSharedPtr<GLGameObject>& gameObject)
	{
		this->GameObject = gameObject.get();
	}

	virtual ~GLTransform()
	{
		this->Parent = nullptr;
	}

	void Update()
	{
		UpdatePosition();
		UpdateRotation();
		UpdateScale();

		UpdateWorldToLocalMatrix();
		UpdateLocalToWorldMatrix();
	}

	void UpdatePosition()
	{
		this->Position = this->LocalPosition;
		if (this->Parent != nullptr)
		{
			this->Position = this->Parent->LocalToWorldMatrix * glm::vec4(this->LocalPosition, 1.0f);
		}
	}

	void UpdateRotation() 
	{
		this->Rotation = this->LocalRotation;
		if (this->Parent != nullptr)
		{
			this->Rotation = this->Parent->Rotation * this->LocalRotation;
		}
	}

	void UpdateScale()
	{
		this->Scale = this->LocalScale;
		if (this->Parent != nullptr)
		{
			this->Scale = this->Parent->Scale * this->LocalScale;
		}
	}

	void UpdateLocalToWorldMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(this->Scale);
		glm::mat4 rotationMatrix = glm::toMat4(this->Rotation);
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->Position);

		this->LocalToWorldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}

	void UpdateWorldToLocalMatrix()
	{
		if (this->Parent == nullptr)
		{
			this->WorldToLocalMatrix = glm::mat4(1.0f);
		}
		else
		{
			this->WorldToLocalMatrix = glm::inverse(this->Parent->LocalToWorldMatrix);
		}
	}

	glm::vec3 GetPosition()
	{
		if (this->Parent != nullptr)
		{
			return this->Parent->GetLocalToWorldMatrix() * glm::vec4(this->LocalPosition, 1.0f);
		}

		return this->LocalPosition;
	}

	glm::quat GetRotation()
	{
		if (this->Parent != nullptr)
		{
			return this->Parent->GetRotation() * this->LocalRotation;
		}

		return this->LocalRotation;
	}

	glm::vec3 GetScale()
	{
		if (this->Parent != nullptr)
		{
			return this->Parent->GetScale() * this->LocalScale;
		}

		return this->LocalScale;
	}

	glm::mat4 GetLocalToWorldMatrix()
	{
		return 
			glm::scale(this->GetScale()) *
			glm::toMat4(this->GetRotation()) *
			glm::translate(glm::mat4(1.0f), this->GetPosition());
	}

	glm::mat4 GetWorldToLocalMatrix()
	{
		if (this->Parent == nullptr)
		{
			return glm::mat4(1.0f);
		}
		else
		{
			return glm::inverse(this->Parent->GetLocalToWorldMatrix());
		}
	}

	glm::vec3 GetEulerAngles()
	{
		return glm::eulerAngles(this->GetRotation());
	}

	glm::vec3 GetLocalEulerAngles()
	{
		return glm::eulerAngles(this->LocalRotation);
	}

	glm::vec3 GetLocalAngleAxis()
	{
		auto Rotation = this->LocalRotation;
		float xSquare = Rotation.x * Rotation.x;
		float ySquare = Rotation.y * Rotation.y;
		float zSquare = Rotation.z * Rotation.z;
		float wSquare = Rotation.w * Rotation.w;

		float sinSquare = xSquare + ySquare + zSquare;

		if (sinSquare > 0.0f)
		{
			float sinTheta = sqrt(sinSquare);
			float k = 2.0f * atan2(sinTheta, Rotation.w) / sinTheta;

			return glm::vec3(
				Rotation.x * k,
				Rotation.y * k,
				Rotation.z * k
			);
		}

		return glm::vec3(
			Rotation.x * 2.0f,
			Rotation.y * 2.0f,
			Rotation.z * 2.0f
		);
	}

	glm::vec3 GetLocalAxis()
	{
		return glm::normalize(this->GetLocalAngleAxis());
	}

	float GetLocalAngle()
	{
		auto angleAxis = this->GetLocalAngleAxis();
		return angleAxis.x / glm::normalize(angleAxis).x;
	}

	glm::vec3 GetAngleAxis()
	{
		auto Rotation = this->GetRotation();
		float xSquare = Rotation.x * Rotation.x;
		float ySquare = Rotation.y * Rotation.y;
		float zSquare = Rotation.z * Rotation.z;
		float wSquare = Rotation.w * Rotation.w;

		float sinSquare = xSquare + ySquare + zSquare;

		if (sinSquare > 0.0f)
		{
			float sinTheta = sqrt(sinSquare);
			float k = 2.0f * atan2(sinTheta, Rotation.w) / sinTheta;

			return glm::vec3(
				Rotation.x * k,
				Rotation.y * k,
				Rotation.z * k
			);
		}

		return glm::vec3(
			Rotation.x * 2.0f,
			Rotation.y * 2.0f,
			Rotation.z * 2.0f
		);
	}

	glm::vec3 GetAxis()
	{
		return glm::normalize(this->GetAngleAxis());
	}

	float GetAngle()
	{
		auto angleAxis = this->GetAngleAxis();
		return angleAxis.x / glm::normalize(angleAxis).x;
	}

	void SetLocalPosition(float x, float y, float z)
	{
		this->LocalPosition.x = x;
		this->LocalPosition.y = y;
		this->LocalPosition.z = z;
	}

	void SetLocalPosition(const glm::vec3& position)
	{
		this->LocalPosition = position;
	}

	void SetPosition(float x, float y, float z)
	{
		SetPosition(glm::vec3(x, y, z));
	}

	void SetPosition(const glm::vec3& position)
	{
		this->LocalPosition = glm::vec3(this->GetWorldToLocalMatrix() * glm::vec4(position, 1.0f));
	}

	void SetLocalRotation(float x, float y, float z, float w)
	{
		this->LocalRotation = glm::normalize(glm::quat(x, y, z, w));
	}

	void SetLocalRotation(const glm::quat& rotation)
	{
		this->LocalRotation = glm::normalize(rotation);
	}

	void SetRotation(float x, float y, float z, float w)
	{
		if (this->Parent == nullptr)
		{
			this->SetLocalRotation(x, y, z, w);

			return;
		}

		this->LocalRotation = glm::normalize(glm::inverse(this->Parent->GetRotation()) * glm::quat(x, y, z, w));
	}

	void SetRotation(const glm::quat& rotation)
	{
		if (this->Parent == nullptr)
		{
			this->SetLocalRotation(rotation);

			return;
		}
		
		this->LocalRotation = glm::normalize(glm::inverse(this->Parent->GetRotation()) * rotation);
	}

	void SetLocalScale(float x, float y, float z)
	{
		this->LocalScale = glm::vec3(x, y, z);
	}

	void SetLocalScale(const glm::vec3& scale)
	{
		this->LocalScale = scale;
	}

	void SetScale(float x, float y, float z)
	{
		if (this->Parent == nullptr)
		{
			this->SetLocalScale(x, y, z);

			return;
		}

		auto parentRotation = this->Parent->GetRotation();
		auto parentScale = this->Parent->GetScale();

		if (parentScale.x != 0.0f)
		{
			this->LocalScale.x = x / parentScale.x;
		}

		if (parentScale.y != 0.0f)
		{
			this->LocalScale.y = y / parentScale.y;
		}

		if (parentScale.z != 0.0f)
		{
			this->LocalScale.z = z / parentScale.z;
		}
	}

	void SetScale(const glm::vec3& scale)
	{
		this->SetScale(scale.x, scale.y, scale.z);
	}

	void SetAngleAxis(float angle, const glm::vec3& axis)
	{
		if (this->Parent != nullptr)
		{
			this->SetLocalRotation(glm::inverse(this->Parent->GetRotation()) * glm::angleAxis(angle, axis));
		}
		else
		{
			this->SetLocalAngleAxis(angle, axis);
		}
	}

	void SetEulerAngles(float x, float y, float z)
	{
		if (this->Parent != nullptr)
		{
			this->SetLocalRotation(glm::inverse(this->Parent->GetRotation()) * glm::quat(glm::vec3(x, y, z)));
		}
		else
		{
			this->SetLocalEulerAngles(x, y, z);
		}
	}

	void SetEulerAngles(const glm::vec3& euler)
	{
		this->SetEulerAngles(euler.x, euler.y, euler.z);
	}

	void SetLocalAngleAxis(float angle, const glm::vec3& axis)
	{
		this->SetLocalRotation(glm::angleAxis(angle, axis));
	}

	void SetLocalEulerAngles(float x, float y, float z)
	{
		this->SetLocalRotation(glm::quat(glm::vec3(x, y, z)));
	}

	void SetLocalEulerAngles(const glm::vec3& euler)
	{
		this->SetLocalRotation(glm::quat(euler));
	}

	void Translate(float x, float y, float z)
	{
		this->Translate(glm::vec3(x, y, z));
	}

	void Translate(glm::vec3 translation)
	{
		auto worldPosition = this->GetPosition();
		this->SetPosition(worldPosition + translation);
	}

	void Rotate(float x, float y, float z)
	{
		this->Rotate(y, glm::vec3(0.0f, 1.0f, 0.0f));
		this->Rotate(x, glm::vec3(1.0f, 0.0f, 0.0f));
		this->Rotate(z, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Rotate(const glm::vec3& euler)
	{
		this->Rotate(euler.x, euler.y, euler.z);
	}

	void Rotate(float angle, const glm::vec3& axis)
	{
        this->SetRotation(glm::angleAxis(angle, axis) * this->GetRotation());
	}

	void RotateAround(const glm::vec3& point, float angle, const glm::vec3& axis)
	{
		auto worldPosition = this->GetPosition();

		glm::quat rotation = glm::normalize(glm::angleAxis(angle, axis));

		this->SetPosition(point + rotation * (worldPosition - point));
		this->Rotate(angle, axis);
	}

	void LookAt(const glm::vec3& eye, const glm::vec3& up)
	{
		auto viewMatrix = glm::lookAt(eye, this->GetPosition(), up);
	}

	void SetParent(const GLSharedPtr<GLTransform>& parent)
	{
		if (parent == this->Parent)
		{
			return;
		}

		this->Parent = parent;
	}

	glm::vec3 LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat LocalRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat Rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 LocalToWorldMatrix = glm::mat4(1.0f);
	glm::mat4 WorldToLocalMatrix = glm::mat4(1.0f);

	GLSharedPtr<GLTransform> Parent = nullptr;
	GLGameObject* GameObject = nullptr;

private:
	bool bUpdated = false;
};