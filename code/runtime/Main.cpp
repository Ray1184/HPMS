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
    Options opts(true, false, true, false, 5, false);
    CustomLogic* logic = hpms::SafeNew<HPMSLogic>();
    Perspective pers(static_cast<float>(glm::radians(60.0)), 0.5f, 20.0f);
    Simulator sim("HPMS Test", 320, 200, false, opts, pers, logic);
    try
    {
        sim.Start();
    } catch (std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    hpms::SafeDelete(logic);

#if !defined(_DEBUG) && !defined(NDEBUG)
    std::stringstream ss;
    ss << "Start memory dump report.\n------------------------------" << std::endl;
    size_t leaks = 0;
    for (const auto& pair : hpms::gAllocationsMap)
    {
        ss << pair.first << ": " << pair.second << std::endl;
        leaks += pair.second;
    }
    ss << std::endl;
    if (leaks == 0) {
        ss << "OK, no potential memory leaks detected!" << std::endl;
    } else {
        ss << "WARNING, " << leaks << " potential memory leaks detected!" << std::endl;
    }
    ss << "------------------------------";
    LOG_DEBUG(ss.str().c_str());
    LOG_DEBUG("End memory dump report.");
#endif
    return 0;
}
