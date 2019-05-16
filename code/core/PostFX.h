/*!
 * File PostFX.h
 */

#pragma once

#include "../common/HPMSObject.h"
#include "Shader.h"
#include <string>

namespace hpms
{

    struct Param
    {
        Param()
        {}

        int i;
        float f;
        std::string s;
        glm::vec3 v3;
        glm::mat4 m4;
    };

    class PostFX : public HPMSObject
    {
    public:
        virtual const std::string GetVSFileName() const = 0;

        virtual const std::string GetFSFileName() const = 0;

        virtual void DefineShader(Shader* shader) = 0;

        virtual void ProcessShader(Shader* shader, std::unordered_map<std::string, Param> params) = 0;

        virtual const float GetRatio() const = 0;
    };
}
