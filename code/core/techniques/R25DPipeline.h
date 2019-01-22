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

        void Init(Window* window, Scene* scene, Renderer* renderer) override
        {

            scene3DShader = PipelineUtils::Create3DSceneShader();
            sceneLayersShader = PipelineUtils::CreateLayersSceneShader();

            for (Mesh mesh : scene->GetMeshes())
            {

                renderer->MeshInit(mesh);
                if (mesh.IsTextured())
                {
                    Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                    if (tex)
                    {
                        renderer->TextureInit(*tex);
                    }
                }

            }

            for (std::string picPath : scene->GetPicturePaths())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(picPath);
                if (tex)
                {
                    renderer->TextureInit(*tex);
                }
            }


            renderer->QuadMeshInit();

            LOG_DEBUG("Retro 2.5D pipeline initialized.");
        }

        void Render(Window* window, Scene* scene, Camera* camera, Renderer* renderer) override
        {
            window->UpdateProjectionMatrix();
            PipelineUtils::RenderScene(window, camera, scene, scene3DShader, sceneLayersShader, false, renderer);

        }

        void Cleanup(Scene* scene, Renderer* renderer) override
        {
            // Cleanup is intended only for GPU resources, not for physical data.
            hpms::CGAPIManager::Instance().FreeShaders();
            for (Mesh mesh : scene->GetMeshes())
            {
                renderer->MeshCleanup(mesh);
                if (mesh.IsTextured())
                {
                    Texture* tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                    if (tex)
                    {
                        renderer->TextureCleanup(*tex);
                    }
                }
            }

            for (std::string texPath : scene->GetPicturePaths())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(texPath);
                if (tex)
                {
                    renderer->TextureCleanup(*tex);
                }
            }

            renderer->QuadMeshCleanup();

            LOG_DEBUG("Retro 2.5D pipeline cleanup done.");
        }

    private:

        Shader* scene3DShader;
        Shader* sceneLayersShader;
    };


}
