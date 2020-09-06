/*!
 * File SceneNode.h
 */

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../Actor.h"
#include "../../common/Utils.h"
#include "../RenderObject.h"
#include "../Names.h"
#include "../Transformation.h"

namespace hpms
{

    class SceneNode : public RenderObject, Actor
    {
    public:
        explicit SceneNode(const std::string& pname) : name(pname),
                                                       parent(nullptr),
                                                       actor(nullptr),
                                                       localTransform(glm::mat4(1.0)),
                                                       worldTransform(glm::mat4(1.0)),
                                                       position(0.0, 0.0, 0.0),
                                                       scale(1.0, 1.0, 1.0),
                                                       rotation(glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)))
        {}

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

        void UpdateTree();

        SceneNode* FindInTree(const std::string& name);

        std::vector<Actor*> GetActorsList();

        void DeleteAllActors();

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



        const glm::mat4& GetWorldTransform() const override
        {
            return worldTransform;
        }

        void SetWorldTransform(const glm::mat4& worldTransform) override
        {
            SceneNode::worldTransform = worldTransform;
        }

        inline bool IsVisible() const override
        {
            return false;
        }


        inline const std::string Name() const override
        {
            return "SceneNode";
        }


        inline void SetPosition(const glm::vec3& position) override
        {
            SceneNode::position = position;
        }

        inline const glm::vec3& GetPosition() const override
        {
            return position;
        }

        inline void SetRotation(const glm::quat& rotation) override
        {
            SceneNode::rotation = rotation;
        }

        inline const glm::quat& GetRotation() const override
        {
            return rotation;
        }

        inline void SetScale(const glm::vec3& scale) override
        {
            SceneNode::scale = scale;
        }

        inline const glm::vec3& GetScale() const override
        {
            return scale;
        }




    private:
        std::string name;
        SceneNode* parent;
        Actor* actor;
        std::vector<SceneNode*> children;
        glm::mat4 localTransform;
        glm::mat4 worldTransform;
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat rotation;
    };
}
