/*!
 * File Scene.h
 */

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "AdvModelItem.h"
#include "Mesh.h"
#include "Entity.h"
#include "LayerPicture.h"

namespace hpms
{

    struct RenderQueue
    {
        std::vector<float> depthBuckets;

        std::vector<RenderObject*> allRenderObjects;

        std::unordered_map<float, std::vector<RenderObject*>> elements;
    };


    class Scene
    {
    public:
        inline void AddRenderObject(RenderObject* obj)
        {
            if (std::find(renderQueue.allRenderObjects.begin(), renderQueue.allRenderObjects.end(), obj) ==
                renderQueue.allRenderObjects.end())
            {
                renderQueue.allRenderObjects.push_back(obj);

                if (auto* entity = dynamic_cast<Entity*>(obj))
                {
                    for (Mesh mesh : entity->GetModelItem()->GetMeshes())
                    {
                        if (std::find(meshes.begin(), meshes.end(), mesh) == meshes.end())
                        {
                            meshes.push_back(mesh);
                        }

                    }
                }

                if (auto* pic = dynamic_cast<LayerPicture*>(obj))
                {
                    if (std::find(picturePaths.begin(), picturePaths.end(), pic->GetImagePath()) == picturePaths.end())
                    {
                        picturePaths.push_back(pic->GetImagePath());
                    }
                }
            }
        }


        inline void UpdateBuckets()
        {
            renderQueue.depthBuckets.clear();
            renderQueue.elements.clear();
            for (RenderObject* obj : renderQueue.allRenderObjects)
            {
                if (std::find(renderQueue.depthBuckets.begin(), renderQueue.depthBuckets.end(),
                              obj->GetVirtualDepth()) == renderQueue.depthBuckets.end())
                {
                    renderQueue.depthBuckets.push_back(obj->GetVirtualDepth());
                }
                renderQueue.elements[obj->GetVirtualDepth()].push_back(obj);
            }

            std::sort(renderQueue.depthBuckets.begin(), renderQueue.depthBuckets.end(), std::greater<float>());
        }

        inline RenderQueue& GetRenderQueue()
        {
            return renderQueue;
        }

        inline const std::vector<Mesh>& GetMeshes() const
        {
            return meshes;
        }


        inline const glm::vec3& GetAmbientLight() const
        {
            return ambientLight;
        }


        inline void SetAmbientLight(const glm::vec3& ambientLight)
        {
            Scene::ambientLight = ambientLight;
        }

        inline const std::vector<std::string>& GetPicturePaths() const
        {
            return picturePaths;
        }

    private:
        RenderQueue renderQueue;
        std::vector<Mesh> meshes;
        std::vector<std::string> picturePaths;
        glm::vec3 ambientLight;
    };
}
