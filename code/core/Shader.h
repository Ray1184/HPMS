/*!
 * File Shader.h
 */

#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Material.h"

namespace hpms
{
    class Shader : public HPMSObject
    {
    public:
        virtual void Init() = 0;

        virtual void CreateUniform(const std::string& name) = 0;

        virtual void CreateMaterialUniform(const std::string& name) = 0;

        virtual void SetUniform(const std::string& name, const glm::mat4& val) = 0;

        virtual void SetUniform(const std::string& name, size_t size, const glm::mat4*& val) = 0;

        virtual void SetUniform(const std::string& name, int val) = 0;

        virtual void SetUniform(const std::string& name, float val) = 0;

        virtual void SetUniform(const std::string& name, const glm::vec3& val) = 0;

        virtual void SetUniform(const std::string& name, const glm::vec4& val) = 0;

        virtual void SetUniform(const std::string& name, const hpms::Material& val) = 0;

        virtual void CreateVS(const std::string& code) = 0;

        virtual void CreateFS(const std::string& code) = 0;

        virtual void Link() = 0;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual void Cleanup() = 0;
    };
}
