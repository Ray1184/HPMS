/*!
 * File Transformation.h
 */

#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "AdvModelItem.h"


namespace hpms
{
    class Transformation
    {
    public:
        Transformation() :
                modelMatrix(glm::mat4(1.0)),
                modelViewMatrix(glm::mat4(1.0))
        {}

        inline static glm::mat4 UpdateGenericViewMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::mat4& matrix)
        {
            glm::mat4 rotMat = glm::eulerAngleXY(glm::radians(rotation.x), glm::radians(rotation.y));
            const glm::mat4 mult = matrix * rotMat;
            return glm::translate(mult, glm::vec3(-position.x, -position.y, -position.z));
        }

        inline glm::mat4& BuildModelMatrix(hpms::AdvModelItem* modelItem)
        {
            const glm::mat4 transMat = glm::translate(modelMatrix, modelItem->GetPosition());
            const glm::mat4 transRotMat = transMat * glm::mat4_cast(modelItem->GetRotation());
            const glm::mat4 transRotScalMat = glm::scale(transRotMat, modelItem->GetScale());
            modelMatrix = transRotScalMat;
            return modelMatrix;

        }

        /*
        std::string PrintMatrix(const glm::mat4& m) {
            std::stringstream ss;
            ss << "[" << m[0][0] << "]" << "[" << m[0][1] << "]" << "[" << m[0][2] << "]" << "[" << m[0][3] << "]" << std::endl;
            ss << "[" << m[1][0] << "]" << "[" << m[1][1] << "]" << "[" << m[1][2] << "]" << "[" << m[1][3] << "]" << std::endl;
            ss << "[" << m[2][0] << "]" << "[" << m[2][1] << "]" << "[" << m[2][2] << "]" << "[" << m[2][3] << "]" << std::endl;
            ss << "[" << m[3][0] << "]" << "[" << m[3][1] << "]" << "[" << m[3][2] << "]" << "[" << m[3][3] << "]" << std::endl;
            std::cout << ss.str().c_str() << std::endl;
        }
        */
    private:
        glm::mat4 modelMatrix;
        glm::mat4 modelViewMatrix;
    };
}
