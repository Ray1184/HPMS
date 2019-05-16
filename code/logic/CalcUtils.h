/*!
 * File CalcUtils.h
 */

#pragma once

#include <glm/vec2.hpp>
#include "Room.h"

namespace hpms
{

    inline float CalcHeightOf2DPointInside3DSector(const Sector& sec, const glm::vec2& pos)
    {
        float det = (sec.z2 - sec.z3) * (sec.x1 - sec.x3) + (sec.x3 - sec.x2) * (sec.z1 - sec.z3);
        float l1 = ((sec.z2 - sec.z3) * (pos.x - sec.x3) + (sec.x3 - sec.x2) * (pos.y - sec.z3)) / det;
        float l2 = ((sec.z3 - sec.z1) * (pos.x - sec.x3) + (sec.x1 - sec.x3) * (pos.y - sec.z3)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * sec.y1 + l2 * sec.y2 + l3 * sec.y3;
    }

    inline bool Is2DPointInside3DSector(const Sector& sec, const glm::vec2& pos)
    {
        float dX = pos.x - sec.x3;
        float dY = pos.y - sec.z3;
        float dX21 = sec.x3 - sec.x2;
        float dY12 = sec.z2 - sec.z3;
        float d = dY12 * (sec.x1 - sec.x3) + dX21 * (sec.z1 - sec.z3);
        float s = dY12 * dX + dX21 * dY;
        float t = (sec.z3 - sec.z1) * dX + (sec.x1 - sec.x3) * dY;
        bool inside;
        if (d < 0)
        {
            inside = s <= 0 && t <= 0 && s + t >= d;
        } else
        {
            inside = s >= 0 && t >= 0 && s + t <= d;
        }
        return inside;
    }
}