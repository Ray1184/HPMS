/*!
 * File Actor.h
 */

#pragma once

#include <glm/glm.hpp>
#include <utility>
#include <functional>
#include "../common/HPMSObject.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/quaternion.hpp>

namespace hpms
{


    class Actor : public HPMSObject
    {


    public:

        virtual void SetPosition(const glm::vec3& position) = 0;

        virtual const glm::vec3& GetPosition() const = 0;

        virtual void SetRotation(const glm::quat& rotation) = 0;

        virtual const glm::quat& GetRotation() const = 0;

        virtual void SetScale(const glm::vec3& scale) = 0;

        virtual const glm::vec3& GetScale() const = 0;

        virtual const glm::mat4& GetWorldTransform() const = 0;

        virtual void SetWorldTransform(const glm::mat4& worldTransform) = 0;


    };
}


