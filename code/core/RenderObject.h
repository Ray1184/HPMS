/**
 * File RenderObject.h
 */
#pragma once

#include <string>

namespace hpms
{

    class RenderObject
    {
    public:
        virtual bool IsVisible() const = 0;

        virtual float GetVirtualDepth() const = 0;

        virtual unsigned int GetTypeId() const = 0;
    };
}
