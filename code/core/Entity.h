/*!
 * File Entity.h
 */

#pragma once

#include <glm/detail/type_quat.hpp>
#include <vector>
#include "../common/Utils.h"
#include "Actor.h"
#include "AdvModelItem.h"

namespace hpms
{
    class Entity : public Actor
    {

    private:
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat rotation;
        bool visible;
        std::vector<std::pair<std::function<void(Actor&)>, std::function<void(Actor&, float)>>> controllers;
        unsigned int animCurrentFrameIndex;
        unsigned int animCurrentIndex;
        bool animPlay;
        bool animLoop;
        const AdvModelItem* modelItem;

    public:

        Entity() : animCurrentFrameIndex(0),
                   animCurrentIndex(0),
                   animPlay(false),
                   animLoop(false),
                   position(0.0, 0.0, 0.0),
                   scale(1.0, 1.0, 1.0),
                   visible(true)
        {}

        Entity(const AdvModelItem* modelItem) : animCurrentFrameIndex(0),
                                                animCurrentIndex(0),
                                                animPlay(false),
                                                animLoop(false),
                                                position(0.0, 0.0, 0.0),
                                                scale(1.0, 1.0, 1.0),
                                                visible(true),
                                                modelItem(modelItem)
        {}

        inline const glm::vec3& GetPosition() const
        {
            return position;
        }

        inline void SetPosition(const glm::vec3& position)
        {
            Entity::position = position;
        }

        inline const glm::vec3& GetScale() const
        {
            return scale;
        }

        inline void SetScale(const glm::vec3& scale)
        {
            Entity::scale = scale;
        }

        inline const glm::quat& GetRotation() const
        {
            return rotation;
        }

        inline void SetRotation(const glm::quat& rotation)
        {
            Entity::rotation = rotation;
        }

        inline virtual void AddController(
                std::pair<std::function<void(Actor&)>, std::function<void(Actor&, float)>> callback) override
        {
            controllers.push_back(callback);
        }

        inline bool IsVisible() const
        {
            return visible;
        }

        inline void SetVisible(bool visible)
        {
            Entity::visible = visible;
        }

        inline const std::vector<std::pair<std::function<void(Actor&)>, std::function<void(Actor&, float)>>>&
        GetControllers() const
        {
            return controllers;
        }

        inline const AdvModelItem* GetModelItem() const
        {
            return modelItem;
        }

        inline void SetModelItem(const AdvModelItem* modelItem)
        {
            Entity::modelItem = modelItem;
        }

        inline unsigned int GetAnimCurrentFrameIndex() const
        {
            return animCurrentFrameIndex;
        }

        inline void SetAnimCurrentFrameIndex(unsigned int animCurrentFrameIndex)
        {
            Entity::animCurrentFrameIndex = animCurrentFrameIndex;
        }

        inline bool IsAnimPlay() const
        {
            return animPlay;
        }

        inline void SetAnimPlay(bool animPlay)
        {
            Entity::animPlay = animPlay;
        }

        inline bool IsAnimLoop() const
        {
            return animLoop;
        }

        inline void SetAnimLoop(bool animLoop)
        {
            Entity::animLoop = animLoop;
        }

        inline unsigned int GetAnimCurrentIndex() const
        {
            return animCurrentIndex;
        }

        inline void SetAnimCurrentIndex(unsigned int animCurrentIndex)
        {
            Entity::animCurrentIndex = animCurrentIndex;
        }
    };
}
