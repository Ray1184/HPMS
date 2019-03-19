/*!
 * File Actor.h
 */

#pragma once

#include <glm/glm.hpp>
#include <utility>
#include <functional>

namespace hpms
{


    class Actor
    {


    public:

        virtual void SetPosition(const glm::vec3& position) = 0;

        virtual const glm::vec3& GetPosition() const = 0;

        virtual void SetRotation(const glm::quat& rotation) = 0;

        virtual const glm::quat& GetRotation() const = 0;

        virtual void SetScale(const glm::vec3& scale) = 0;

        virtual const glm::vec3& GetScale() const = 0;

    };
}


