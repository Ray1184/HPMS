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


        std::vector<Animation> animations;

        unsigned int currentAnimationIndex;

    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(meshes),
                PODS_OPT(animations)

        );

        inline const std::vector<Animation>& GetAnimations() const
        {
            return animations;
        }

        inline void SetAnimations(const std::vector<Animation>& animations)
        {
            AdvModelItem::animations = animations;
        }

        inline unsigned int GetCurrentAnimationIndex() const
        {
            return currentAnimationIndex;
        }

        inline void SetCurrentAnimationIndex(unsigned int currentAnimationIndex)
        {
            AdvModelItem::currentAnimationIndex = currentAnimationIndex;
        }
    };
}


