/*!
 * File Scene.h
 */

#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "AdvModelItem.h"
#include "Mesh.h"
#include "Entity.h"

namespace hpms
{
    class Scene
    {
    public:
        inline void AddEntity(Entity* entity)
        {
            const AdvModelItem* model = entity->GetModelItem();
            modelsMap[model].push_back(entity);
        }

        const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& GetModelsMap() const
        {
            return modelsMap;
        }

        inline const glm::vec3& GetAmbientLight() const
        {
            return ambientLight;
        }


        inline void SetAmbientLight(const glm::vec3& ambientLight)
        {
            Scene::ambientLight = ambientLight;
        }

    private:
        std::unordered_map<const hpms::AdvModelItem*, std::vector<Entity*>> modelsMap;
        glm::vec3 ambientLight;
    };
}
