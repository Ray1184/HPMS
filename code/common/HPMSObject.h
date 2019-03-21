/*!
 * File HPMSObject.h
 */

#pragma once

#include <string>

namespace hpms
{
    struct HPMSObject
    {


        virtual const std::string Name() const = 0;

    };
}
