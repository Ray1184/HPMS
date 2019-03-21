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
            pictureShader = PipelineUtils::CreatePictureShader();
            depthShader = PipelineUtils::CreateDepthShader();

            if (Picture* pic = scene->GetBackPicture())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
                if (tex)
                {
                    renderer->TextureInit(*tex);
                }
            }

            if (Picture* pic = scene->GetDepthPicture())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
                if (tex)
                {
                    renderer->TextureInit(*tex);
                }
            }

            for (const auto& entry : scene->GetItemsMap())
            {
                for (const Mesh& mesh : entry.first->GetMeshes())
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
            }

            for (Picture* const& pic : scene->GetForePictures())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
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
            renderer->ClearAllBuffers();

            // For R25D scenarios, rendering flow is:
            // 1) Background images and depth clear
            // 2) Depth maps
            // 3) 3D models and depth clear
            // 4) Foreground images
            PipelineUtils::RenderPictures(scene, pictureShader, renderer, false);
            renderer->ClearDepthBuffer();
            PipelineUtils::RenderDepthMask(scene, window, depthShader, renderer);
            PipelineUtils::RenderScene(scene, window, camera, scene3DShader, renderer, false);
            renderer->ClearDepthBuffer();
            PipelineUtils::RenderPictures(scene, pictureShader, renderer, true);

        }

        void Cleanup(Scene* scene, Renderer* renderer) override
        {
            // Cleanup is intended only for GPU resources (except shaders), not for physical data.
            hpms::CGAPIManager::Instance().FreeShaders();

            if (Picture* pic = scene->GetBackPicture())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
                if (tex)
                {
                    renderer->TextureCleanup(*tex);
                }
            }

            if (Picture* pic = scene->GetDepthPicture())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
                if (tex)
                {
                    renderer->TextureCleanup(*tex);
                }
            }

            for (const auto& entry : scene->GetItemsMap())
            {
                for (const Mesh& mesh : entry.first->GetMeshes())
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
            }

            for (Picture* const& pic : scene->GetForePictures())
            {
                Texture* tex = ResourceCache::Instance().GetTexture(pic->GetImagePath());
                if (tex)
                {
                    renderer->TextureCleanup(*tex);
                }
            }

            renderer->QuadMeshCleanup();

            LOG_DEBUG("Retro 2.5D pipeline cleanup done.");
        }

        inline const std::string Name() const override
        {
            return "R25DPipeline";
        }

    private:

        Shader* scene3DShader;
        Shader* pictureShader;
        Shader* depthShader;

    };


}
