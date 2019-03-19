/*!
 * File R25DGameState.h
 */

#pragma once

#include "../GameState.h"
#include "../../core/techniques/R25DPipeline.h"

namespace hpms
{
    class R25DGameState : public GameState
    {
    public:
        R25DGameState(LuaVM* pvm) : GameState(pvm), clear(false)
        {
            pipeline = hpms::SafeNew<R25DPipeline>();
        }

        virtual ~R25DGameState()
        {
            CCleanup();
        }

        inline void CInit() override
        {

        }

        inline void CUpdate() override
        {

        }

        inline void CCleanup() override
        {
            if (!clear)
            {
                clear = true;
                hpms::SafeDelete(pipeline);
            }
        }

    private:
        bool clear;


    };
}
