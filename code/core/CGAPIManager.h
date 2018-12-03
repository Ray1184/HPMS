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

namespace hpms
{
    class CGAPIManager
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

        inline void FreeShaders()
        {
            for (Shader* shader : shadersReferences)
            {
                shader->Cleanup();
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

    private:
        CGAPIManager()
        {};

        CGAPIManager(const CGAPIManager&);

        CGAPIManager& operator=(const CGAPIManager&);

        std::vector<hpms::Shader*> shadersReferences;
        hpms::Window* currentWindow;
    };
}
