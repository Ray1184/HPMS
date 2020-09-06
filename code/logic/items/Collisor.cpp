/*!
 * File Collisor.cpp
 */

#include "Collisor.h"

void hpms::Collisor::CheckAndMove(const glm::vec3& nextPosition, const glm::vec2 direction)
{


    Triangle nextTriangle = hpms::SampleTriangle(nextPosition, walkMap, tolerance);

    if (nextTriangle.GetSectorId() != UNDEFINED_SECTOR || ignore || walkMap->DummyMap())
    {
        // No collision, go to next triangle.
        actor->SetPosition(nextPosition);
        currentTriangle = nextTriangle;
        return;
    } else
    {
        // Check potential collisions.
        for (const auto& side : nextTriangle.GetPerimetralSides())
        {
            vec2pair_t sidePair = hpms::GetSideCoordsFromTriangle(nextTriangle, side);
            float t = hpms::IntersectRayLineSegment(actor->GetPosition(), direction, sidePair.a, sidePair.b);
            // Correct side.
            if (t > -1)
            {
                glm::vec2 n = glm::normalize(hpms::Perperndicular(sidePair.b - sidePair.a));
                glm::vec3 v = nextPosition - actor->GetPosition();
                glm::vec2 vn = n * glm::dot(glm::vec2(v.x, v.z), n);
                glm::vec2 vt = glm::vec2(v.x, v.z) - vn;
                glm::vec3 correctPosition = glm::vec3(actor->GetPosition().x + vt.x, actor->GetPosition().y,
                                                      actor->GetPosition().z + vt.y);

                Triangle correctTriangle = hpms::SampleTriangle(correctPosition, walkMap, tolerance);

                if (correctTriangle.GetSectorId() != UNDEFINED_SECTOR)
                {
                    // Calculated position is good, move actor to calculated position.
                    actor->SetPosition(correctPosition);

                    // Assign for safe, but correctTriangle should be the original.
                    currentTriangle = correctTriangle;
                }
                return;
            }
        }
    }
}

