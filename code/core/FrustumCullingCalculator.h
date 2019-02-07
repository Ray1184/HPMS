/*!
 * File FrustumCullingCalculator.h
 */

#pragma once

#include <glm/glm.hpp>
#include <math.h>

namespace hpms
{
    class FrustumCullingCalculator
    {
    private:
        float nxX, nxY, nxZ, nxW;
        float pxX, pxY, pxZ, pxW;
        float nyX, nyY, nyZ, nyW;
        float pyX, pyY, pyZ, pyW;
        float nzX, nzY, nzZ, nzW;
        float pzX, pzY, pzZ, pzW;

        inline void Update(const glm::mat4& m, bool allowTestSpheres)
        {
            float invl;
            nxX = m[0][3] + m[0][0];
            nxY = m[1][3] + m[1][0];
            nxZ = m[2][3] + m[2][0];
            nxW = m[3][3] + m[3][0];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(nxX * nxX + nxY * nxY + nxZ * nxZ));
                nxX *= invl;
                nxY *= invl;
                nxZ *= invl;
                nxW *= invl;
            }

            pxX = m[0][3] - m[0][0];
            pxY = m[1][3] - m[1][0];
            pxZ = m[2][3] - m[2][0];
            pxW = m[3][3] - m[3][0];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(pxX * pxX + pxY * pxY + pxZ * pxZ));
                pxX *= invl;
                pxY *= invl;
                pxZ *= invl;
                pxW *= invl;
            }

            nyX = m[0][3] + m[0][1];
            nyY = m[1][3] + m[1][1];
            nyZ = m[2][3] + m[2][1];
            nyW = m[3][3] + m[3][1];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(nyX * nyX + nyY * nyY + nyZ * nyZ));
                nyX *= invl;
                nyY *= invl;
                nyZ *= invl;
                nyW *= invl;
            }

            pyX = m[0][3] - m[0][1];
            pyY = m[1][3] - m[1][1];
            pyZ = m[2][3] - m[2][1];
            pyW = m[3][3] - m[3][1];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(pyX * pyX + pyY * pyY + pyZ * pyZ));
                pyX *= invl;
                pyY *= invl;
                pyZ *= invl;
                pyW *= invl;
            }

            nzX = m[0][3] + m[0][2];
            nzY = m[1][3] + m[1][2];
            nzZ = m[2][3] + m[2][2];
            nzW = m[3][3] + m[3][2];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(nzX * nzX + nzY * nzY + nzZ * nzZ));
                nzX *= invl;
                nzY *= invl;
                nzZ *= invl;
                nzW *= invl;
            }

            pzX = m[0][3] - m[0][2];
            pzY = m[1][3] - m[1][2];
            pzZ = m[2][3] - m[2][2];
            pzW = m[3][3] - m[3][2];
            if (allowTestSpheres)
            {
                invl = (float) (1.0 / sqrt(pzX * pzX + pzY * pzY + pzZ * pzZ));
                pzX *= invl;
                pzY *= invl;
                pzZ *= invl;
                pzW *= invl;
            }

        }

        inline bool SphereInsideFrustum(float x, float y, float z, float r)
        {
            bool inside = true;
            float dist;
            dist = nxX * x + nxY * y + nxZ * z + nxW;
            if (dist >= -r)
            {
                inside &= dist >= r;
                dist = pxX * x + pxY * y + pxZ * z + pxW;
                if (dist >= -r)
                {
                    inside &= dist >= r;
                    dist = nyX * x + nyY * y + nyZ * z + nyW;
                    if (dist >= -r)
                    {
                        inside &= dist >= r;
                        dist = pyX * x + pyY * y + pyZ * z + pyW;
                        if (dist >= -r)
                        {
                            inside &= dist >= r;
                            dist = nzX * x + nzY * y + nzZ * z + nzW;
                            if (dist >= -r)
                            {
                                inside &= dist >= r;
                                dist = pzX * x + pzY * y + pzZ * z + pzW;
                                if (dist >= -r)
                                {
                                    inside &= dist >= r;
                                    return inside;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }

    public:

        inline void Update(const glm::mat4& m)
        {
            Update(m, true);
        }

        inline bool SphereInsideFrustum(const glm::vec3& center, float boundingRadius)
        {
            return SphereInsideFrustum(center.x, center.y, center.z, boundingRadius);
        }


    };
}
