/*!
 * File R25DPipeline.h
 */

#pragma once

#include "../Pipeline.h"
#include "../CGAPIManager.h"
#include "../PipelineUtils.h"

namespace hpms
{
    class R25DPipeline : public hpms::Pipeline
    {
    public:
        R25DPipeline()
        {
            LOG_DEBUG("Retro 2.5D pipeline module created.");
        }

        void Init(Window* window, Scene* scene, Renderer* renderer, FrameBuffer* frameBuffer) override;

        void Render(Window* window, Scene* scene, Camera* camera, Renderer* renderer, FrameBuffer* frameBuffer) override;

        void Cleanup(Scene* scene, Renderer* renderer, FrameBuffer* frameBuffer) override;

        inline const std::string Name() const override
        {
            return "R25DPipeline";
        }

    private:

        Shader* scene3DShader;
        Shader* pictureShader;
        Shader* depthShader;
        Shader* fboShader;
        PostFX* postFx;

    };


}
