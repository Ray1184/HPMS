/*!
 * File Camera.h
 */

#pragma once

#include <glm/glm.hpp>
#include "Transformation.h"

namespace hpms
{
    class Camera
    {
    public:
        Camera() : position(glm::vec3(0, 0, 0)),
                   rotation(glm::vec3(0, 0, 0)),
                   viewMatrix(glm::mat4(1.0))
        {

        }

        Camera(glm::vec3& pposition, glm::vec3& protation) :
                position(pposition),
                rotation(protation),
                viewMatrix(glm::mat4(1.0))
        {

        }

        inline const glm::vec3& GetPosition() const
        {
            return position;
        }

        inline void SetPosition(const glm::vec3& position)
        {
            Camera::position = position;
        }

        inline const glm::vec3& GetRotation() const
        {
            return rotation;
        }

        inline void SetRotation(const glm::vec3& rotation)
        {
            Camera::rotation = rotation;
        }

        inline const glm::mat4& GetViewMatrix() const
        {
            return viewMatrix;
        }

        inline void SetViewMatrix(const glm::mat4& viewMatrix)
        {
            Camera::viewMatrix = viewMatrix;
        }

        inline glm::mat4 UpdateViewMatrix()
        {
            viewMatrix = glm::mat4(1.0);
            viewMatrix = hpms::Transformation::UpdateGenericViewMatrix(position, rotation, viewMatrix);
            return viewMatrix;
        }

    private:

        glm::vec3 position;
        glm::vec3 rotation;
        glm::mat4 viewMatrix;

    };
}
