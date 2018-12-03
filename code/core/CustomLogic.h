/*!
 * File CustomLogic.h
 */

#pragma once

#include "Window.h"

namespace hpms
{
    class CustomLogic
    {
    public:
        virtual void Init(Window* window) = 0;

        virtual void Input(Window* window) = 0;

        virtual void Update() = 0;

        // Dynamic updated disabled.
        /*
        virtual void UpdateRealTime(float tpf) = 0;
         */

        virtual void Render(Window* window) = 0;

        virtual void Cleanup() = 0;

        virtual bool Quit() = 0;
    };
}
