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
        void Init(Window* window, Scene& scene, Renderer* renderer) override
        {

            sceneShader = PipelineUtils::CreateSceneShader();
            auto mapMeshes = scene.GetMeshMap();

            for (auto entry : mapMeshes)
            {
                Mesh mesh = entry.first;
                renderer->MeshInit(mesh);
                if (mesh.IsTextured())
                {
                    Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                    renderer->TextureInit(*tex);
                }
            }

            LOG_DEBUG("Retro 2.5D pipeline initialized.");
        }

        void Render(Window* window, Scene& scene, Camera& camera, Renderer* renderer) override
        {
            renderer->ClearBuffer();
            PipelineUtils::RenderScene(window, camera, scene, sceneShader, transformation, false, renderer);
        }

        void Cleanup(Scene& scene, Renderer* renderer) override
        {
            // Cleanup is intended only for GPU resources, not for physical data.
            hpms::CGAPIManager::Instance().FreeShaders();
            auto mapMeshes = scene.GetMeshMap();
            for (auto entry : mapMeshes)
            {

                Mesh mesh = entry.first;
                renderer->MeshCleanup(mesh);
                if (mesh.IsTextured())
                {
                    Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                    renderer->TextureCleanup(*tex);
                }
            }

            LOG_DEBUG("Retro 2.5D pipeline cleanup done.");
        }

    private:

        Shader* sceneShader;
        Transformation transformation;
    };


}
