/*!
 * File GLDefaultPostFX.h
 */

#pragma once

#include "../../PostFX.h"
#include "../../Names.h"

namespace hpms
{
    class GLDefaultPostFX : public PostFX
    {
    public:

        GLDefaultPostFX(float pratio) : ratio(pratio)
        {
            LOG_DEBUG("OpenGL PostFX module created.");
        }


        inline const std::string GetVSFileName() const override
        {
            return SHADER_FILE_PIXELFX_VERT;
        }

        inline const std::string GetFSFileName() const override
        {
            return SHADER_FILE_PIXELFX_FRAG;
        }

        inline void DefineShader(Shader* shader) override
        {
            shader->CreateUniform(UNIFORM_TEXSAMPLER);
            shader->CreateUniform(UNIFORM_GLOBALALPHA);
        }

        inline void ProcessShader(Shader* shader, std::unordered_map<std::string, Param> params) override
        {
            shader->SetUniform(UNIFORM_TEXSAMPLER, 0);

            float alpha = params[PARAM_GLOBAL_ALPHA].f;
            shader->SetUniform(UNIFORM_GLOBALALPHA, alpha);

        }


        inline const float GetRatio() const override
        {
            return ratio;
        }

        inline const std::string Name() const override
        {
            return "GLDefaultPostFX";
        }

    private:

        float ratio;
    };
}
