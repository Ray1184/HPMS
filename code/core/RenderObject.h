/**
 * File RenderObject.h
 */
#pragma once

#include <string>

namespace hpms
{

    class RenderObject : public HPMSObject
    {
    public:
        virtual bool IsVisible() const = 0;

    };
}
