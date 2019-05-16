/*!
 * File CGAPIManager.h
 */

#pragma once

#include <vector>
#include "Shader.h"
#include "Window.h"
#include "../common/Utils.h"
#include "gl/GLWindow.h"
#include "gl/GLShader.h"
#include "Renderer.h"
#include "gl/GLRenderer.h"
#include "FrameBuffer.h"
#include "gl/GLFrameBuffer.h"
#include "gl/fx/GLDefaultPostFX.h"

namespace hpms
{
    class CGAPIManager : public HPMSObject
    {
    public:

        inline static CGAPIManager& Instance()
        {
            static CGAPIManager inst;
            return inst;
        }

        inline Window* CreateNewWindow(const std::string& title, const unsigned int width, const unsigned int height,
                                    const bool vSync, const Options& options, const Perspective& perspective) {
            // TODO - Unitil now only OpenGL is supported.
            currentWindow = hpms::SafeNew<hpms::GLWindow>(title, width, height, vSync, options, perspective);
            return currentWindow;
        }

        inline Shader* CreateNewShader()
        {
            // TODO - Unitil now only OpenGL is supported.
            hpms::Shader* shader = hpms::SafeNew<hpms::GLShader>();
            shadersReferences.push_back(shader);
            return shader;
        }

        inline Renderer* CreateNewRenderer()
        {
            // TODO - Unitil now only OpenGL is supported.
            currentRenderer = hpms::SafeNew<hpms::GLRenderer>();
            return currentRenderer;
        }

        inline FrameBuffer* CreateNewFrameBuffer(int width, int height)
        {
            // TODO - Unitil now only OpenGL is supported.
            frameBuffer = hpms::SafeNew<hpms::GLFrameBuffer>(width, height, nullptr, nullptr);
            return frameBuffer;
        }

        inline PostFX* CreateNewPostFX(float pixelRatio)
        {
            // TODO - Unitil now only OpenGL Default FX is supported.
            postFx = hpms::SafeNew<hpms::GLDefaultPostFX>(pixelRatio);
            return postFx;
        }
        inline void FreeShaders()
        {
            for (Shader* shader : shadersReferences)
            {
                hpms::SafeDelete(shader);
                LOG_DEBUG("Shader cleanup done.");
            }

            shadersReferences.clear();
        }

        inline void FreeWindow()
        {
            hpms::SafeDelete(currentWindow);
            LOG_DEBUG("Window cleanup done.");
        }

        inline void FreeRenderer()
        {
            hpms::SafeDelete(currentRenderer);
            LOG_DEBUG("Renderer cleanup done.");
        }

        inline void FreeFrameBuffer()
        {
            hpms::SafeDelete(frameBuffer);
            LOG_DEBUG("FrameBuffer cleanup done.");
        }

        inline void FreePostFX()
        {
            hpms::SafeDelete(postFx);
            LOG_DEBUG("PostFX cleanup done.");
        }

        inline const std::string Name() const override
        {
            return "CGAPIManager";
        }

    private:
        CGAPIManager()
        {};

        CGAPIManager(const CGAPIManager&);

        CGAPIManager& operator=(const CGAPIManager&);

        std::vector<hpms::Shader*> shadersReferences;
        hpms::Window* currentWindow;
        hpms::Renderer* currentRenderer;
        hpms::FrameBuffer* frameBuffer;
        hpms::PostFX* postFx;

    };
}
