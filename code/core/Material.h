/*!
 * File Material.h
 */

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <pods/pods.h>
#include <pods/buffers.h>
#include <pods/binary.h>

namespace hpms
{
    class Material
    {
    private:
        glm::vec4 ambient;
        glm::vec4 diffuse;
        std::string textureName;


    public:
        PODS_SERIALIZABLE(
                1,
                PODS_OPT(ambient.r),
                PODS_OPT(ambient.g),
                PODS_OPT(ambient.b),
                PODS_OPT(ambient.a),
                PODS_OPT(diffuse.r),
                PODS_OPT(diffuse.g),
                PODS_OPT(diffuse.b),
                PODS_OPT(diffuse.a),
                PODS_OPT(textureName)
        )

        inline const glm::vec4& GetAmbient() const
        {
            return ambient;
        }

        inline void SetAmbient(const glm::vec4& ambient)
        {
            Material::ambient = ambient;
        }

        inline const glm::vec4& GetDiffuse() const
        {
            return diffuse;
        }

        inline void SetDiffuse(const glm::vec4& diffuse)
        {
            Material::diffuse = diffuse;
        }

        inline const std::string& GetTextureName() const
        {
            return textureName;
        }

        inline void SetTextureName(const std::string& textureName)
        {
            Material::textureName = textureName;
        }

    };
}

