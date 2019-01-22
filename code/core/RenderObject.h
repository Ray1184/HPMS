/**
 * File RenderObject.h
 */
#pragma once

namespace hpms
{

    class RenderObject
    {
    public:
        virtual bool IsVisible() const = 0;

        virtual float GetVirtualDepth() const = 0;
    };
}
