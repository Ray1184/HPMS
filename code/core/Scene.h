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
#include "items/Entity.h"
#include "items/Picture.h"

namespace hpms
{


    class Scene : HPMSObject
    {
    public:
        Scene() : ambientLight(glm::vec3(1.0, 1.0, 1.0)), alpha(1.0)
        {}

        inline void AddRenderObject(RenderObject* obj)
        {

            if (auto* entity = dynamic_cast<Entity*>(obj))
            {

                itemsMap[entity->GetModelItem()].push_back(entity);

            }

            if (auto* pic = dynamic_cast<Picture*>(obj))
            {
                if (pic->GetMode() == PictureMode::FOREGROUND)
                {
                    if (std::find(forePictures.begin(), forePictures.end(), pic) == forePictures.end())
                    {
                        forePictures.push_back(pic);
                    }
                } else if (pic->GetMode() == PictureMode::BACKGROUND)
                {
                    backPicture = pic;
                } else if (pic->GetMode() == PictureMode::DEPTH_MASK)
                {
                    depthPicture = pic;
                }
            }

        }

        inline const glm::vec3& GetAmbientLight() const
        {
            return ambientLight;
        }


        inline void SetAmbientLight(const glm::vec3& ambientLight)
        {
            Scene::ambientLight = ambientLight;
        }


        inline const std::vector<Picture*>& GetForePictures() const
        {
            return forePictures;
        }

        inline Picture* GetBackPicture() const
        {
            return backPicture;
        }

        inline Picture* GetDepthPicture() const
        {
            return depthPicture;
        }

        inline const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& GetItemsMap() const
        {
            return itemsMap;
        }

        inline const std::string Name() const override
        {
            return "Scene";
        }

        inline float GetAlpha() const
        {
            return alpha;
        }

        inline void SetAlpha(float alpha)
        {
            Scene::alpha = alpha;
        }

    private:

        std::unordered_map<const hpms::AdvModelItem*, std::vector<hpms::Entity*>> itemsMap;
        std::vector<Picture*> forePictures;
        Picture* backPicture;
        Picture* depthPicture;
        glm::vec3 ambientLight;
        float alpha;
    };
}
