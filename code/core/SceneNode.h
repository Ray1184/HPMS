/*!
 * File SceneNode.h
 */

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Actor.h"
#include "../common/Utils.h"
#include "RenderObject.h"
#include "Names.h"

namespace hpms
{

    class SceneNode : public RenderObject
    {
    public:
        SceneNode(const std::string& pname) : name(pname),
                                              parent(nullptr),
                                              localTransform(glm::mat4(1.0)),
                                              worldTransform(glm::mat4(1.0))
        {}

        ~SceneNode()
        {
            for (SceneNode* child : children)
            {
                hpms::SafeDelete(child);
            }
        }

        inline SceneNode* GetParent() const
        {
            return parent;
        }

        inline void SetParent(SceneNode* parent)
        {
            SceneNode::parent = parent;
        }

        inline Actor* GetActor() const
        {
            return actor;
        }

        inline void SetActor(Actor* actor)
        {
            SceneNode::actor = actor;
        }

        inline const std::string& GetName() const
        {
            return name;
        }

        inline const std::vector<SceneNode*>& GetChildren() const
        {
            return children;
        }

        inline const glm::mat4& GetLocalTransform() const
        {
            return localTransform;
        }

        inline const glm::mat4& GetWorldTransform() const
        {
            return worldTransform;
        }

        inline bool IsVisible() const override
        {
            return false;
        }

        inline float GetVirtualDepth() const override
        {
            return 0;
        }

        inline unsigned int GetTypeId() const override
        {
            return OBJ_TYPE_NODE;
        }

    private:
        std::string name;
        SceneNode* parent;
        Actor* actor;
        std::vector<SceneNode*> children;
        glm::mat4 localTransform;
        glm::mat4 worldTransform;
    };
}
