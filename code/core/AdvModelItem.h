/*!
 * File AdvModelItem.h
 */

#pragma once

#include <unordered_map>
#include "StdModelItem.h"
#include "Animation.h"


namespace hpms
{
    class AdvModelItem : public StdModelItem
    {
    private:

        std::string key;
        std::vector<Animation> animations;


    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(meshes),
                PODS_OPT(animations)

        );

        AdvModelItem(const std::string& key) : key(key)
        {}

        AdvModelItem()
        {
            char buffer[32];
            hpms::RandomString(buffer, 32);
            key = std::string(buffer);
        }

        inline const std::vector<Animation>& GetAnimations() const
        {
            return animations;
        }

        inline void SetAnimations(const std::vector<Animation>& animations)
        {
            AdvModelItem::animations = animations;
        }





    };
}


