/*!
 * File CustomLogic.h
 */

#pragma once

#include "Window.h"
#include "../common/HPMSObject.h"

namespace hpms
{
    class CustomLogic : public HPMSObject
    {
    public:
        virtual void Init(Window* window) = 0;

        virtual void Input(Window* window) = 0;

        virtual void Update(Window* window) = 0;

        virtual void Render(Window* window) = 0;

        virtual void Cleanup() = 0;

        virtual bool Quit() = 0;
    };
}
