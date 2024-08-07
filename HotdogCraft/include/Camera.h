#pragma once

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

namespace HotdogCraft
{
	struct Camera
	{
		float pitch{ 0.f };
		float yaw{ 270.f };

		glm::vec3 position{ 0.f, 2.f, 0.f };
		glm::vec3 target;

		glm::vec3 front{ 0.f, 0.f, -1.f };
		glm::vec3 forward{ 0.f, 0.f, -1.f };
		glm::vec3 right;
		glm::vec3 up;

		const glm::vec3 worldUp{ 0.f, 1.f, 0.f };

		void update()
		{
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			forward.x = cos(glm::radians(yaw));
			forward.z = sin(glm::radians(yaw));

			right = glm::normalize(glm::cross(front, worldUp));
			up = glm::normalize(glm::cross(right, front));
		}
	};
}