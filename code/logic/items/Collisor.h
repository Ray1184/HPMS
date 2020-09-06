/*!
 * File Collisor.h
 */

#pragma once

#include "../../core/Actor.h"
#include "WalkMap.h"
#include "../SectorUtils.h"
#include <glm/gtx/perpendicular.hpp>




namespace hpms
{
    class Collisor : public Actor
    {
    private:
        hpms::Actor* actor;
        hpms::WalkMap* walkMap;
        float tolerance;
        hpms::Triangle currentTriangle;
        bool ignore;
    public:

        Collisor(Actor* actor, WalkMap* walkMap, float tolerance) : actor(actor), walkMap(walkMap),
                                                                    tolerance(tolerance), ignore(false)
        {}


        inline void SetPosition(const glm::vec3& position) override
        {
            actor->SetPosition(position);
        }

        inline const glm::vec3& GetPosition() const override
        {
            return actor->GetPosition();
        }

        inline void SetRotation(const glm::quat& rotation) override
        {
            actor->SetRotation(rotation);
        }

        inline const glm::quat& GetRotation() const override
        {
            return actor->GetRotation();
        }

        inline void SetScale(const glm::vec3& scale) override
        {
            actor->SetScale(scale);
        }

        inline const glm::vec3& GetScale() const override
        {
            return actor->GetScale();
        }

        inline const glm::mat4& GetWorldTransform() const override
        {
            return actor->GetWorldTransform();
        }

        inline void SetWorldTransform(const glm::mat4& worldTransform) override
        {
            actor->SetWorldTransform(worldTransform);
        }

        inline const std::string Name() const override
        {
            return "Collisor";
        }

        void CheckAndMove(const glm::vec3& nextPosition, const glm::vec2 direction);

    };
}
