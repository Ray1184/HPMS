/*!
 * File SectorUtils.cpp
 */

#include "SectorUtils.h"

hpms::Triangle hpms::SampleTriangle(const glm::vec3& pos, hpms::WalkMap* walkMap, float tolerance)
{
    if (walkMap->DummyMap())
    {
        LOG_ERROR("Cannot sample triangle on dummy map.");
    }
    for (const auto& sector : walkMap->GetRoomModelItem()->GetSectors())
    {
        for (const auto& tri : sector.GetTriangles())
        {
            if (hpms::Is2DPointInside3DSector(tri, glm::vec2(pos.x, pos.z), tolerance))
            {
                return tri;
            }
        }
    }

    return Triangle(UNDEFINED_SECTOR);

}

glm::vec2 hpms::GetSideCoordFromSideIndex(const hpms::Triangle& tri, unsigned int idx)
{
    switch (idx)
    {
        case 1:
            return glm::vec2(tri.x1, tri.z1);
        case 2:
            return glm::vec2(tri.x2, tri.z2);
        case 3:
            return glm::vec2(tri.x3, tri.z3);
        default:
            std::stringstream ss;
            ss << "Index id " << idx << " not allowed for external side" << std::endl;
            LOG_ERROR(ss.str().c_str());
    }
}

hpms::vec2pair_t hpms::GetSideCoordsFromTriangle(const hpms::Triangle& tri, const hpms::Side& side)
{
    for (const auto& s : tri.GetPerimetralSides())
    {
        if (s == side)
        {
            return {GetSideCoordFromSideIndex(tri, s.idx1), GetSideCoordFromSideIndex(tri, s.idx2)};
        }
    }
    return {0, 0, 0, 0};

}
