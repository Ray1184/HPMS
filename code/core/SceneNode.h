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
        explicit SceneNode(const std::string& pname) : name(pname),
                                                       parent(nullptr),
                                                       actor(nullptr),
                                                       localTransform(glm::mat4(1.0)),
                                                       worldTransform(glm::mat4(1.0)) {}

        ~SceneNode()
        {
            for (SceneNode* child : children)
            {
                hpms::SafeDelete(child);
            }
        }

        inline void AddChild(SceneNode* child)
        {
            children.push_back(child);
            child->parent = this;
        }

        inline void UpdateTree()
        {
            if (parent != nullptr)
            {
                worldTransform = parent->worldTransform * localTransform;
            } else
            {
                worldTransform = localTransform;
            }

            for (SceneNode* child : children)
            {
                child->UpdateTree();
            }
        }

        inline SceneNode* FindInTree(const std::string& name)
        {
            SceneNode* res = nullptr;
            if (this->name.compare(name) == 0)
            {
                res = this;
            } else
            {
                for (SceneNode* child : this->children)
                {
                    res = FindInTree(name);
                    if (res != nullptr)
                    {
                        break;
                    }
                }
            }
            return res;
        }

        inline SceneNode* GetParent() const
        {
            return parent;
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


        inline const std::string Name() const override
        {
            return "SceneNode";
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
