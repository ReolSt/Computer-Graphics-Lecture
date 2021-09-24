#pragma once

#include <gl/glew.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtx/transform.hpp>
#include <gl/glm/gtx/quaternion.hpp>

class GLGameObject;

class GLTransform
{
public:
	static glm::vec4 ApplyTransform(GLTransform& transform, glm::vec3 vector)
	{
		glm::vec4 result(vector, 1.0);

		result = transform.transform_matrix * result;

		auto current_transform = transform.parent;
		while (current_transform)
		{
			result = current_transform->transform_matrix * result;
			current_transform = current_transform->parent;
		}

		return result;
	}
public:
	GLTransform(GLGameObject& game_object)
		: game_object(game_object)
	{
		this->Update();
	}

	virtual ~GLTransform() { }

	void Translate(GLfloat x, GLfloat y, GLfloat z)
	{
		this->position += glm::vec3(x, y, z);
	}

	void Translate(glm::vec3 translation)
	{
		this->position += translation;
	}

	void Update()
	{
		glm::mat4 scale_matrix = glm::scale(this->scale);
		glm::mat4 rotation_matrix = glm::toMat4(this->rotation);
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), this->position);

		this->transform_matrix = translation_matrix * rotation_matrix * scale_matrix;
	}

	glm::vec3 GetWorldPosition()
	{
		return glm::vec3(GLTransform::GLTransform::ApplyTransform(*this->parent, this->position));
	}

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 transform_matrix;

	std::shared_ptr<GLTransform> parent = nullptr;
	GLGameObject& game_object;
};