/*!
 * File R25DPipeline.cpp
 */

#include "R25DPipeline.h"

void hpms::R25DPipeline::Init(Window* window, Scene* scene, Renderer* renderer, FrameBuffer* frameBuffer)
{


    scene3DShader = PipelineUtils::Create3DSceneShader();
    pictureShader = PipelineUtils::CreatePictureShader();
    depthShader = PipelineUtils::CreateDepthShader();


    if (Picture* pic = scene->GetBackPicture())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
        if (tex)
        {
            renderer->TextureInit(*tex);
        }
    }

    if (Picture* pic = scene->GetDepthPicture())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
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
                Texture* tex = ResourceItemsCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                if (tex)
                {
                    renderer->TextureInit(*tex);
                }
            }

        }
    }

    for (Picture* const& pic : scene->GetForePictures())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
        if (tex)
        {
            renderer->TextureInit(*tex);
        }
    }


    renderer->QuadMeshInit();

    frameBuffer->Init();
    float ratio = hpms::GetConf("PIXEL_RATIO", 4);

    postFx = CGAPIManager::Instance().CreateNewPostFX(ratio);
    fboShader = PipelineUtils::CreateFrameBufferShader(postFx);
    frameBuffer->SetPostFx(postFx);
    frameBuffer->SetFboShader(fboShader);

    LOG_DEBUG("Retro 2.5D pipeline initialized.");
}

void
hpms::R25DPipeline::Render(Window* window, Scene* scene, Camera* camera, Renderer* renderer, FrameBuffer* frameBuffer)
{
    scene->UpdateNodes();
    Param alpha;
    alpha.f = scene->GetAlpha();
    frameBuffer->SetParam(PARAM_GLOBAL_ALPHA, alpha);
    frameBuffer->PreRendering();
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


    frameBuffer->PostRendering();

}

void hpms::R25DPipeline::Cleanup(Scene* scene, Renderer* renderer, FrameBuffer* frameBuffer)
{
    // Cleanup is intended only for GPU resources (except shaders and FX), not for physical data.
    hpms::CGAPIManager::Instance().FreeShaders();

    if (Picture* pic = scene->GetBackPicture())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
        if (tex)
        {
            renderer->TextureCleanup(*tex);
        }
    }

    if (Picture* pic = scene->GetDepthPicture())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
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
                Texture* tex = ResourceItemsCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                if (tex)
                {
                    renderer->TextureCleanup(*tex);
                }
            }
        }
    }

    for (Picture* const& pic : scene->GetForePictures())
    {
        Texture* tex = ResourceItemsCache::Instance().GetTexture(pic->GetImagePath());
        if (tex)
        {
            renderer->TextureCleanup(*tex);
        }
    }

    renderer->QuadMeshCleanup();
    frameBuffer->Cleanup();
    CGAPIManager::Instance().FreePostFX();

    LOG_DEBUG("Retro 2.5D pipeline cleanup done.");
}
