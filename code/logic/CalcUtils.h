/*!
 * File CalcUtils.h
 */

#pragma once

#include <glm/vec2.hpp>
#include "RoomModelItem.h"

namespace hpms
{

    float CalcHeightOf2DPointInside3DSector(const Triangle& sec, const glm::vec2& pos);

    bool Is2DPointInside3DSector(const Triangle& sec, const glm::vec2& pos, float tolerance = 0);

    bool TestSidesOverlap(const hpms::Triangle& t, const hpms::Triangle& o, unsigned int side);

    std::vector<hpms::Side>
    CalculatePerimetralSides(const hpms::Triangle& t, const std::vector<hpms::Triangle>& triangles);

    float
    IntersectRayLineSegment(float originX, float originY, float dirX, float dirY, float aX, float aY, float bX,
                            float bY);


    inline float
    IntersectRayLineSegment(const glm::vec3& origin, const glm::vec2& dir, const glm::vec2& a, const glm::vec2& b)
    {
        return IntersectRayLineSegment(origin.x, origin.z, dir.x, dir.y, a.x, a.y, b.x, b.y);
    }

    inline glm::vec2 Perperndicular(const glm::vec2 origin)
    {
        return {origin.y, -origin.x};
    }






}