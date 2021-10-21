#pragma once

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
		: GameObject(gameObject)
	{ }

	virtual ~GLTransform() { }

	glm::vec3 GetPosition()
	{
		if (this->Parent != nullptr)
		{
			auto parentPosition = this->Parent->GetPosition();
			auto parentRotation = this->Parent->GetRotation();
			auto parentScale = this->Parent->GetScale();

			glm::mat4 scaleMatrix = glm::scale(parentScale);
			glm::mat4 rotationMatrix = glm::toMat4(parentRotation);
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), parentPosition);

			return translationMatrix * rotationMatrix * scaleMatrix * glm::vec4(this->LocalPosition, 1.0f);
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

	void Translate(float x, float y, float z)
	{
		this->Translate(glm::vec3(x, y, z));
	}

	void Translate(glm::vec3 translation)
	{
		auto worldPosition = this->GetPosition();
		this->SetPosition(worldPosition + translation);
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
		this->LocalPosition = glm::vec3(this->WorldToLocalMatrix() * glm::vec4(position, 1.0f));
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
		this->LocalRotation = glm::rotate(this->LocalRotation, angle, axis);
	}

	void RotateAround(const glm::vec3& point, float angle, const glm::vec3& axis)
	{
		glm::vec3 worldPosition = this->GetPosition();

		this->SetPosition(point + glm::angleAxis(angle, axis) * (worldPosition - point));
		this->Rotate(angle, axis);
	}

	void SetLocalScale(float x, float y, float z)
	{
		this->LocalScale.x = x;
		this->LocalScale.y = y;
		this->LocalScale.z = z;
	}

	glm::vec3 GetEulerAngles()
	{
		return glm::eulerAngles(this->GetRotation());
	}

	glm::vec3 GetLocalEulerAngles()
	{
		return glm::eulerAngles(this->LocalRotation);
	}

	glm::vec3 GetLocalAxis()
	{
		float angleHalf = glm::acos(this->LocalRotation.w);

		return glm::vec3(
			this->LocalRotation.x / glm::sin(angleHalf),
			this->LocalRotation.y / glm::sin(angleHalf),
			this->LocalRotation.z / glm::sin(angleHalf)
		);
	}

	float GetLocalAngle()
	{
		return glm::acos(this->LocalRotation.w);
	}

	glm::vec3 GetAxis()
	{
		auto Rotation = this->GetRotation();
		float angleHalf = glm::acos(Rotation.w);

		return glm::vec3(
			Rotation.x / glm::sin(angleHalf),
			Rotation.y / glm::sin(angleHalf),
			Rotation.z / glm::sin(angleHalf)
		);
	}

	float GetAngle()
	{
		return glm::acos(this->GetRotation().w);
	}

	void SetAngleAxis(float angle, const glm::vec3& axis)
	{
		if (this->Parent != nullptr)
		{
			this->LocalRotation = glm::inverse(this->Parent->GetRotation()) * glm::angleAxis(angle, axis);
		}
		else
		{
			SetLocalAngleAxis(angle, axis);
		}
	}

	void SetEulerAngles(float x, float y, float z)
	{
		if (this->Parent != nullptr)
		{
			this->LocalRotation = glm::inverse(this->Parent->GetRotation()) * glm::quat(glm::vec3(x, y, z));
		}
	}

	void SetLocalAngleAxis(float angle, const glm::vec3& axis)
	{
		this->LocalRotation = glm::angleAxis(angle, axis);
	}

	void SetLocalEulerAngles(float x, float y, float z)
	{
		this->LocalRotation = glm::quat(glm::vec3(x, y, z));
	}

	glm::mat4 LocalToWorldMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(this->GetScale());
		glm::mat4 rotationMatrix = glm::toMat4(this->GetRotation());
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->GetPosition());

		return translationMatrix * rotationMatrix * scaleMatrix;
	}

	glm::mat4 WorldToLocalMatrix()
	{
		return glm::inverse(this->Parent->LocalToWorldMatrix());
	}

	glm::vec3 LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat LocalRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);

	GLSharedPtr<GLTransform> Parent = nullptr;
	GLGameObject* GameObject;
};