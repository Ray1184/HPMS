/*!
 * File StdModelItem.h
 */

#pragma once

#include <vector>
#include <glm/detail/type_quat.hpp>
#include "Actor.h"
#include "Mesh.h"
#include <pods/pods.h>
#include <pods/buffers.h>
#include <pods/binary.h>


namespace hpms
{
    class StdModelItem : public Actor
    {
    protected:
        std::vector<Mesh> meshes;

        // Transient data
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat rotation;
        bool visible;
        std::vector<std::pair<std::function<void(Actor&)>, std::function<void(Actor&, float)>>> controllers;

    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(meshes)
        )


        inline const glm::vec3& GetPosition() const
        {
            return position;
        }

        inline void SetPosition(const glm::vec3& position)
        {
            StdModelItem::position = position;
        }

        inline const glm::vec3& GetScale() const
        {
            return scale;
        }

        inline void SetScale(const glm::vec3& scale)
        {
            StdModelItem::scale = scale;
        }

        inline const glm::quat& GetRotation() const
        {
            return rotation;
        }

        inline void SetRotation(const glm::quat& rotation)
        {
            StdModelItem::rotation = rotation;
        }

        inline virtual void AddController(
                std::pair<std::function<void(Actor&)>, std::function<void(Actor&, float)>> callback) override
        {
            controllers.push_back(callback);
        }

        inline const std::vector<Mesh>& GetMeshes() const
        {
            return meshes;
        }

        inline void SetMeshes(const std::vector<Mesh>& meshes)
        {
            StdModelItem::meshes = meshes;
        }

        inline bool IsVisible() const
        {
            return visible;
        }

        inline void SetVisible(bool visible)
        {
            StdModelItem::visible = visible;
        }
    };


}
