#pragma once

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtx/transform.hpp>
#include <gl/glm/gtx/quaternion.hpp>

class GLGameObject;

class GLTransform
{
public:
	GLTransform(const std::shared_ptr<GLGameObject>& game_object)
		: game_object(game_object)
	{ }

	GLTransform(GLGameObject* game_object)
		: game_object(game_object)
	{ }

	virtual ~GLTransform() { }

	glm::vec3 Position()
	{
		if (this->parent != nullptr)
		{
			auto parent_position = this->parent->Position();
			auto parent_rotation = this->parent->Rotation();
			auto parent_scale = this->parent->Scale();

			glm::mat4 scale_matrix = glm::scale(parent_scale);
			glm::mat4 rotation_matrix = glm::toMat4(parent_rotation);
			glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), parent_position);

			return translation_matrix * rotation_matrix * scale_matrix * glm::vec4(this->local_position, 1.0f);
		}

		return this->local_position;
	}

	glm::quat Rotation()
	{
		if (this->parent != nullptr)
		{
			return this->local_rotation * this->parent->Rotation();
		}

		return this->local_rotation;
	}

	glm::vec3 Scale()
	{
		if (this->parent != nullptr)
		{
			return this->local_scale * this->parent->Scale();
		}

		return this->local_scale;
	}

	void Translate(GLfloat x, GLfloat y, GLfloat z)
	{
		this->local_position += glm::vec3(x, y, z);
	}

	void Translate(glm::vec3 translation)
	{
		this->local_position += translation;
	}

	void SetPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		this->local_position.x = x;
		this->local_position.y = y;
		this->local_position.z = z;
	}

	void Rotate(GLfloat x, GLfloat y, GLfloat z)
	{
		this->local_rotation = glm::rotate(this->local_rotation, y, glm::vec3(0.0f, 1.0f, 0.0f));
		this->local_rotation = glm::rotate(this->local_rotation, x, glm::vec3(1.0f, 0.0f, 0.0f));
		this->local_rotation = glm::rotate(this->local_rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void SetEulerAngles(GLfloat x, GLfloat y, GLfloat z)
	{
		this->local_rotation = glm::normalize(glm::quat(glm::vec3(x, y, z)));
	}

	void SetScale(GLfloat x, GLfloat y, GLfloat z)
	{
		this->local_scale.x = x;
		this->local_scale.y = y;
		this->local_scale.z = z;
	}

	glm::vec3 EulerAngles()
	{
		return glm::eulerAngles(this->local_rotation);
	}

	glm::mat4 localToWorldMatrix()
	{
		glm::mat4 scale_matrix = glm::scale(this->Scale());
		glm::mat4 rotation_matrix = glm::toMat4(this->Rotation());
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), this->Position());

		return translation_matrix * rotation_matrix * scale_matrix;
	}

	glm::vec3 local_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat local_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 local_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	std::shared_ptr<GLTransform> parent = nullptr;
	std::shared_ptr<GLGameObject> game_object = nullptr;
};