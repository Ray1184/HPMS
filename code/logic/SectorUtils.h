/*!
 * File InteractionUtils.h
 */

#pragma once

#include "RoomModelItem.h"
#include "items/WalkMap.h"
#include "../common/Utils.h"
#include "CalcUtils.h"
#include "../core/Actor.h"

namespace hpms
{
    Triangle SampleTriangle(const glm::vec3& pos, hpms::WalkMap* walkMap, float tolerance);

    inline Triangle SampleTriangle(hpms::Actor* actor, hpms::WalkMap* walkMap, float tolerance)
    {
        return SampleTriangle(actor->GetPosition(), walkMap, tolerance);
    }

    inline bool
    ActorInsideSector(hpms::Actor* actor, const hpms::Sector& sector, hpms::WalkMap* walkMap, float tolerance)
    {
        return ActorInsideSector(actor, sector.GetId(), walkMap, tolerance);
    }

    inline bool
    ActorInsideSector(hpms::Actor* actor, const std::string& sectorName, hpms::WalkMap* walkMap, float tolerance)
    {
        return sectorName == SampleTriangle(actor, walkMap, tolerance).GetSectorId();
    }

    typedef struct vec2pair
    {
        glm::vec2 a;
        glm::vec2 b;

        vec2pair(float ax, float ay, float bx, float by)
        {
            a = glm::vec2(ax, ay);
            b = glm::vec2(bx, by);
        }

        vec2pair(const glm::vec2& _a, const glm::vec2& _b)
        {
            a = glm::vec2(_a.x, _a.y);
            b = glm::vec2(_b.x, _b.y);
        }
    } vec2pair_t;

    glm::vec2 GetSideCoordFromSideIndex(const hpms::Triangle& tri, unsigned int idx);

    vec2pair_t GetSideCoordsFromTriangle(const hpms::Triangle& tri, const hpms::Side& side);
}
