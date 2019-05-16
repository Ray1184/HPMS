/*!
 * File Entity.h
 */

#pragma once

#include <glm/detail/type_quat.hpp>
#include <vector>
#include "../../common/Utils.h"
#include "../Actor.h"
#include "../AdvModelItem.h"
#include "../RenderObject.h"
#include "../Names.h"

namespace hpms
{


    class Entity : public Actor, public RenderObject
    {

    private:
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat rotation;
        bool visible;
        unsigned int animCurrentFrameIndex;
        unsigned int animCurrentIndex;
        bool animPlay;
        bool animLoop;
        AdvModelItem* modelItem{};

    public:

        Entity() : animCurrentFrameIndex(0),
                   animCurrentIndex(0),
                   animPlay(false),
                   animLoop(false),
                   position(0.0, 0.0, 0.0),
                   scale(1.0, 1.0, 1.0),
                   visible(true),
                   rotation(glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)))
        {}

        explicit Entity(AdvModelItem* modelItem) : animCurrentFrameIndex(0),
                                                   animCurrentIndex(0),
                                                   animPlay(false),
                                                   animLoop(false),
                                                   position(0.0, 0.0, 0.0),
                                                   scale(1.0, 1.0, 1.0),
                                                   visible(true),
                                                   modelItem(modelItem),
                                                   rotation(glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)))
        {}

        inline const glm::vec3& GetPosition() const override
        {
            return position;
        }

        inline void SetPosition(const glm::vec3& position) override
        {
            Entity::position = position;
        }

        inline const glm::vec3& GetScale() const override
        {
            return scale;
        }

        inline void SetScale(const glm::vec3& scale) override
        {
            Entity::scale = scale;
        }

        inline const glm::quat& GetRotation() const override
        {
            return rotation;
        }

        inline void SetRotation(const glm::quat& rotation) override
        {
            Entity::rotation = rotation;
        }

        inline bool IsVisible() const override
        {
            return visible;
        }

        inline void SetVisible(bool visible)
        {
            Entity::visible = visible;
        }

        inline const AdvModelItem* GetModelItem() const
        {
            return modelItem;
        }

        inline void SetModelItem(AdvModelItem* modelItem)
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


        inline const std::string Name() const override
        {
            return "Entity";
        }
    };
}
