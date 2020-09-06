/*!
 * File PipelineUtils.cpp
 */

#include "PipelineUtils.h"

hpms::Shader* hpms::PipelineUtils::Create3DSceneShader()
{
    std::string vertCode = hpms::ReadFile(SHADER_FILE_SCENE_VERT);
    std::string fragCode = hpms::ReadFile(SHADER_FILE_SCENE_FRAG);
    Shader* sceneShader = CGAPIManager::Instance().CreateNewShader();
    sceneShader->Init();
    sceneShader->CreateVS(vertCode);
    sceneShader->CreateFS(fragCode);
    sceneShader->Link();

    sceneShader->CreateUniform(UNIFORM_MODELVIEWMATRIX);
    sceneShader->CreateUniform(UNIFORM_PROJMATRIX);
    sceneShader->CreateUniform(UNIFORM_TEXSAMPLER);
    sceneShader->CreateMaterialUniform(UNIFORM_MATERIAL);
    sceneShader->CreateUniform(UNIFORM_AMBIENTLIGHT);
    sceneShader->CreateUniform(UNIFORM_JOINTSMATRIX);
    sceneShader->CreateUniform(UNIFORM_DIFFUSEINTENSITY);
    return sceneShader;
}

hpms::Shader* hpms::PipelineUtils::CreateFrameBufferShader(PostFX* postFx)
{
    Shader* fboShader = CGAPIManager::Instance().CreateNewShader();
    std::string vertCode = hpms::ReadFile(postFx->GetVSFileName());
    std::string fragCode = hpms::ReadFile(postFx->GetFSFileName());

    fboShader->Init();
    fboShader->CreateVS(vertCode);
    fboShader->CreateFS(fragCode);
    fboShader->Link();
    postFx->DefineShader(fboShader);
    return fboShader;
}

hpms::Shader* hpms::PipelineUtils::CreatePictureShader()
{
    std::string vertCode = hpms::ReadFile(SHADER_FILE_PICTURE_VERT);
    std::string fragCode = hpms::ReadFile(SHADER_FILE_PICTURE_FRAG);
    Shader* layerShader = CGAPIManager::Instance().CreateNewShader();
    layerShader->Init();
    layerShader->CreateVS(vertCode);
    layerShader->CreateFS(fragCode);
    layerShader->Link();

    layerShader->CreateUniform(UNIFORM_TEXSAMPLER);
    layerShader->CreateUniform(UNIFORM_ALPHA);
    layerShader->CreateUniform(UNIFORM_X);
    layerShader->CreateUniform(UNIFORM_Y);
    return layerShader;
}

hpms::Shader* hpms::PipelineUtils::CreateDepthShader()
{
    std::string vertCode = hpms::ReadFile(SHADER_FILE_DEPTHMASK_VERT);
    std::string fragCode = hpms::ReadFile(SHADER_FILE_DEPTHMASK_FRAG);
    Shader* depthShader = CGAPIManager::Instance().CreateNewShader();
    depthShader->Init();
    depthShader->CreateVS(vertCode);
    depthShader->CreateFS(fragCode);
    depthShader->Link();

    depthShader->CreateUniform(UNIFORM_TEXSAMPLER);
    depthShader->CreateUniform(UNIFORM_PROJMATRIX);
    depthShader->CreateUniform(UNIFORM_ZNEAR);
    depthShader->CreateUniform(UNIFORM_ZFAR);
    return depthShader;
}

void hpms::PipelineUtils::RenderScene(Scene* scene, Window* window, Camera* camera, Shader* scene3DShader,
                                      Renderer* renderer, bool gui)
{
    scene3DShader->Bind();


    glm::mat4 projMatrix = window->GetProjMatrix();

    scene3DShader->SetUniform(UNIFORM_PROJMATRIX, projMatrix);
    scene3DShader->SetUniform(UNIFORM_DIFFUSEINTENSITY, gui ? 1.0f : 0.1f);
    scene3DShader->SetUniform(UNIFORM_AMBIENTLIGHT, scene->GetAmbientLight());

    renderer->ModelsDraw(scene->GetItemsMap(), scene3DShader, camera, window, RenderCallback);

    scene3DShader->Unbind();
}

void hpms::PipelineUtils::RenderPictures(Scene* scene, Shader* pictureShader, Renderer* renderer, bool foreground)
{
    pictureShader->Bind();

    pictureShader->SetUniform(UNIFORM_TEXSAMPLER, 0);
    if (foreground)
    {
        for (Picture* const& pic : scene->GetForePictures())
        {
            pictureShader->SetUniform(UNIFORM_ALPHA, pic->GetAlpha());
            pictureShader->SetUniform(UNIFORM_X, pic->GetX());
            pictureShader->SetUniform(UNIFORM_Y, pic->GetY());
            renderer->QuadsDraw(pic->GetImagePath());
        }
    } else
    {
        if (scene->GetBackPicture())
        {
            renderer->QuadsDraw(scene->GetBackPicture()->GetImagePath());
        }
    }
    pictureShader->Unbind();
}

void hpms::PipelineUtils::RenderDepthMask(Scene* scene, Window* window, Shader* depthShader, Renderer* renderer)
{
    depthShader->Bind();
    depthShader->SetUniform(UNIFORM_TEXSAMPLER, 0);
    depthShader->SetUniform(UNIFORM_PROJMATRIX, window->GetProjMatrix());
    depthShader->SetUniform(UNIFORM_ZNEAR, window->GetPerspective().zNear);
    depthShader->SetUniform(UNIFORM_ZFAR, window->GetPerspective().zFar);
    if (scene->GetDepthPicture())
    {
        renderer->QuadsDraw(scene->GetDepthPicture()->GetImagePath());
    }
    depthShader->Unbind();
}

void hpms::PipelineUtils::RenderCallback(Entity* entity, Shader* shader, Camera* camera, Window* window)
{


    // Model view matrix.
    glm::mat4 modelMatrix = Transformation::BuildModelMatrix(entity);
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    shader->SetUniform(UNIFORM_MODELVIEWMATRIX, modelViewMatrix);

    // Animation management.
    if (!entity->GetModelItem()->GetAnimations().empty() &&
        entity->GetAnimCurrentIndex() < entity->GetModelItem()->GetAnimations().size())
    {

        const Animation* anim = entity->GetModelItem()->GetAnimationWithIndex(
                entity->GetAnimCurrentIndex());
        const Frame* frame = anim->GetFrameWithIndex(entity->GetAnimCurrentFrameIndex());
        const glm::mat4* jointMatrices = &(frame->frameTransformations[0].jointMatrix);
        shader->SetUniform(UNIFORM_JOINTSMATRIX, frame->frameTransformations.size(), jointMatrices);

    }

}
