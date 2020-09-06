/*!
 * File FrustumCullingCalculator.h
 */

#pragma once

#include <glm/glm.hpp>
#include <math.h>
#include "../common/HPMSObject.h"

namespace hpms
{
    class FrustumCullingCalculator : public HPMSObject
    {
    private:
        float nxX, nxY, nxZ, nxW;
        float pxX, pxY, pxZ, pxW;
        float nyX, nyY, nyZ, nyW;
        float pyX, pyY, pyZ, pyW;
        float nzX, nzY, nzZ, nzW;
        float pzX, pzY, pzZ, pzW;

        void Update(const glm::mat4& m, bool allowTestSpheres);

        bool SphereInsideFrustum(float x, float y, float z, float r);

    public:

        inline void Update(const glm::mat4& m)
        {
            Update(m, true);
        }

        inline bool SphereInsideFrustum(const glm::vec3& center, float boundingRadius)
        {
            return SphereInsideFrustum(center.x, center.y, center.z, boundingRadius);
        }

        inline const std::string Name() const override
        {
            return "FrustumCullingCalculator";
        }


    };
}
