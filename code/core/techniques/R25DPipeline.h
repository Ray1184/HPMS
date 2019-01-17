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

            for (auto& entry : scene.GetModelsMap())
            {
                const AdvModelItem* item = entry.first;
                for (Mesh mesh : item->GetMeshes())
                {

                    renderer->MeshInit(mesh);
                    if (mesh.IsTextured())
                    {
                        Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                        renderer->TextureInit(*tex);
                    }

                }
            }

            LOG_DEBUG("Retro 2.5D pipeline initialized.");
        }

        void Render(Window* window, Scene& scene, Camera* camera, Renderer* renderer) override
        {
            window->UpdateProjectionMatrix();
            PipelineUtils::RenderScene(window, camera, scene, sceneShader, false, renderer);

        }

        void Cleanup(Scene& scene, Renderer* renderer) override
        {
            // Cleanup is intended only for GPU resources, not for physical data.
            hpms::CGAPIManager::Instance().FreeShaders();
            for (auto& entry : scene.GetModelsMap())
            {
                const AdvModelItem* item = entry.first;
                for (Mesh mesh : item->GetMeshes())
                {
                    renderer->MeshCleanup(mesh);
                    if (mesh.IsTextured())
                    {
                        Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                        renderer->TextureCleanup(*tex);
                    }
                }
            }

            LOG_DEBUG("Retro 2.5D pipeline cleanup done.");
        }

    private:

        Shader* sceneShader;
    };


}
