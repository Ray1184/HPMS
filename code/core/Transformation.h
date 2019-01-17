/*!
 * File Transformation.h
 */

#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include "AdvModelItem.h"
#include "Entity.h"


namespace hpms
{
    class Transformation
    {
    public:
        Transformation()
        {}

        inline static glm::mat4 UpdateGenericViewMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::mat4& matrix)
        {
            glm::mat4 rotMat = glm::eulerAngleXY(rotation.x, rotation.y);
            const glm::mat4 mult = matrix * rotMat;
            return glm::translate(mult, glm::vec3(-position.x, -position.y, -position.z));
        }

        inline static glm::mat4 BuildModelMatrix(hpms::Entity* entity)
        {

            const glm::mat4 rotMat = glm::toMat4(entity->GetRotation());
            const glm::mat4 transMat = glm::translate(glm::mat4(1.0f), entity->GetPosition());
            const glm::mat4 transScalMat = glm::scale(transMat, entity->GetScale());
            glm::mat4 resMat = transScalMat * rotMat;
            return resMat;
        }


    };
}
