/*!
 * File FrameBuffer.h
 */

#pragma once

#include "../common/HPMSObject.h"
#include "PostFX.h"

namespace hpms
{
    class FrameBuffer : public HPMSObject
    {
    public:

        FrameBuffer(int pwidth, int pheight, PostFX* ppostFx, Shader* fboShader) : width(pwidth), height(pheight),
                                                                                   postFx(ppostFx), fboShader(fboShader)
        {}

        inline void SetParam(const std::string& key, const Param& param)
        {
            params.insert(std::make_pair(key, param));
        }

        inline PostFX* GetPostFx() const
        {
            return postFx;
        }

        inline void SetPostFx(PostFX* postFx)
        {
            FrameBuffer::postFx = postFx;
        }


        inline Shader* GetFboShader() const
        {
            return fboShader;
        }

        inline void SetFboShader(Shader* fboShader)
        {
            FrameBuffer::fboShader = fboShader;
        }

        virtual void Init() = 0;

        virtual void PreRendering() = 0;

        virtual void PostRendering() = 0;

        virtual void Cleanup() = 0;

    protected:

        int width;

        int height;

        PostFX* postFx;

        std::unordered_map<std::string, Param> params;

        Shader* fboShader;

    };
}
