/*!
 * File GLFrameBuffer.h
 */

#pragma once

#include <glad/glad.h>
#include "../FrameBuffer.h"
#include "../../common/Utils.h"
#include "GLShader.h"

namespace hpms
{
    class GLFrameBuffer : public FrameBuffer
    {
    public:
        GLFrameBuffer(int pwidth, int pheight, PostFX* ppostFx, Shader* fboShader) : FrameBuffer(pwidth, pheight,
                                                                                                 ppostFx, fboShader),
                                                                                     clear(false), initialized(false)
        {
            LOG_DEBUG("OpenGL frame buffer module created.");
        }

        virtual ~GLFrameBuffer()
        {
            Cleanup();
        }


        void Init() override;

        void PreRendering() override;

        void PostRendering() override;

        void Cleanup() override;

        inline const std::string Name() const override
        {
            return "GLFrameBuffer";
        }

    private:

        bool clear;
        bool initialized;
        GLuint fboId;
        GLuint textId;
        GLuint rboId;
        GLuint quadVao;
        GLuint quadVbo;
        GLuint vaoId;


    };
}
