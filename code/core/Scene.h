/*!
 * File Scene.h
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "AdvModelItem.h"
#include "Mesh.h"

namespace hpms
{
    class Scene
    {
    public:
        inline void AddModel(hpms::AdvModelItem* modelItem)
        {
            std::vector<hpms::Mesh> meshes = modelItem->GetMeshes();
            for (hpms::Mesh mesh : meshes)
            {

                if (meshMap.find(mesh) == meshMap.end())
                {
                    std::vector<hpms::AdvModelItem*> models;
                    models.push_back(modelItem);
                    meshMap.insert({mesh, models});
                } else
                {
                    meshMap[mesh].push_back(modelItem);
                }
            }

        }

        inline const std::unordered_map<Mesh, std::vector<AdvModelItem*>, MeshHasher, MeshEqualFn>& GetMeshMap() const
        {
            return meshMap;
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
        std::unordered_map<hpms::Mesh, std::vector<hpms::AdvModelItem*>, hpms::MeshHasher, hpms::MeshEqualFn> meshMap;
        glm::vec3 ambientLight;
    };
}
