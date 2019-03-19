/**
 * File Main.cpp
 */

#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL


#include "../core/CustomLogic.h"
#include "../core/Simulator.h"
#include "HPMSLogic.h"

using namespace hpms;

int main()
{
    Options opts{true, false, true, false, 5, false};
    CustomLogic* logic = hpms::SafeNew<HPMSLogic>();
    Perspective pers{static_cast<float>(glm::radians(60.0)), 0.5f, 20.0f};
    Simulator sim("HPMS Test", 320, 200, false, opts, pers, logic);
    sim.Start();
    hpms::SafeDelete(logic);
    return 0;
}
