/*!
 * File PipelineUtils.h
 */

#pragma once

#include "Shader.h"
#include "CGAPIManager.h"
#include "../common/Utils.h"
#include "Names.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "LayerPicture.h"

namespace hpms
{
    class PipelineUtils
    {

    public:

        inline static Shader* Create3DSceneShader()
        {
            std::string vertCode = hpms::ReadFile(SHADER_FILE_SCENE_VERT);
            std::string fragCode = hpms::ReadFile(SHADER_FILE_SCENE_FRAG);
            Shader* sceneShader = CGAPIManager::Instance().CreateNewShader();
            sceneShader->CreateVS(vertCode);
            sceneShader->CreateFS(fragCode);
            sceneShader->Link();

            sceneShader->CreateUniform(UNIFORM_VIEWMATRIX);
            sceneShader->CreateUniform(UNIFORM_PROJMATRIX);
            sceneShader->CreateUniform(UNIFORM_MODELMATRIX);
            sceneShader->CreateUniform(UNIFORM_TEXSAMPLER);
            sceneShader->CreateMaterialUniform(UNIFORM_MATERIAL);
            sceneShader->CreateUniform(UNIFORM_AMBIENTLIGHT);
            sceneShader->CreateUniform(UNIFORM_JOINTSMATRIX);
            sceneShader->CreateUniform(UNIFORM_DIFFUSEINTENSITY);
            return sceneShader;
        }

        inline static Shader* CreateLayersSceneShader()
        {
            std::string vertCode = hpms::ReadFile(SHADER_FILE_PICTURE_VERT);
            std::string fragCode = hpms::ReadFile(SHADER_FILE_PICTURE_FRAG);
            Shader* layerShader = CGAPIManager::Instance().CreateNewShader();
            layerShader->CreateVS(vertCode);
            layerShader->CreateFS(fragCode);
            layerShader->Link();

            layerShader->CreateUniform(UNIFORM_TEXSAMPLER);
            layerShader->CreateUniform(UNIFORM_ALPHA);
            layerShader->CreateUniform(UNIFORM_X);
            layerShader->CreateUniform(UNIFORM_Y);
            return layerShader;
        }

        inline static void RenderScene(Window* window, Camera* camera, Scene* scene,
                                       Shader* scene3DShader, Shader* layerShader, bool gui, Renderer* renderer)
        {
            renderer->ClearBuffer();


            // Render pass.
            for (float vDepth : scene->GetRenderQueue().depthBuckets)
            {

                std::vector<RenderObject*> renderObjects = scene->GetRenderQueue().elements[vDepth];

                // TODO - Avoid cast, use two maps instead.
                // Render 3D meshes.
                if (!renderObjects.empty() && dynamic_cast<Entity*>(renderObjects[0]))
                {


                    scene3DShader->Bind();


                    glm::mat4 viewMatrix = camera->GetViewMatrix();
                    glm::mat4 projMatrix = window->GetProjMatrix();

                    scene3DShader->SetUniform(UNIFORM_VIEWMATRIX, viewMatrix);
                    scene3DShader->SetUniform(UNIFORM_PROJMATRIX, projMatrix);
                    scene3DShader->SetUniform(UNIFORM_DIFFUSEINTENSITY, gui ? 1.0f : 0.1f);
                    scene3DShader->SetUniform(UNIFORM_AMBIENTLIGHT, scene->GetAmbientLight());
                    scene3DShader->SetUniform(UNIFORM_TEXSAMPLER, 0);

                    std::unordered_map<Mesh, std::vector<Entity*>, MeshHasher, MeshEqual> meshesToEntitiesMap;

                    for (RenderObject* ro : renderObjects)
                    {
                        if (ro->IsVisible() && dynamic_cast<Entity*>(ro))
                        {
                            Entity* entity = dynamic_cast<Entity*>(ro);
                            for (Mesh mesh : entity->GetModelItem()->GetMeshes())
                            {
                                meshesToEntitiesMap[mesh].push_back(entity);
                            }
                        }


                        renderer->ModelsDraw(meshesToEntitiesMap, scene3DShader, RenderCallback);


                    }

                    scene3DShader->Unbind();

                }
                    // Render layers.
                else if (!renderObjects.empty() && dynamic_cast<LayerPicture*>(renderObjects[0]))
                {
                    layerShader->Bind();

                    layerShader->SetUniform(UNIFORM_TEXSAMPLER, 0);

                    for (RenderObject* ro : renderObjects)
                    {
                        if (ro->IsVisible() && dynamic_cast<LayerPicture*>(ro))
                        {
                            LayerPicture* picture = dynamic_cast<LayerPicture*>(ro);
                            layerShader->SetUniform(UNIFORM_ALPHA, picture->GetAlpha());
                            layerShader->SetUniform(UNIFORM_X, picture->GetX());
                            layerShader->SetUniform(UNIFORM_Y, picture->GetY());
                            renderer->QuadsDraw(picture->GetImagePath());
                        }
                    }


                    layerShader->Unbind();
                }
            }
        }


    private:
        inline static void RenderCallback(Entity* entity, Shader* shader)
        {

            glm::mat4 modelMatrix = Transformation::BuildModelMatrix(entity);
            shader->SetUniform(UNIFORM_MODELMATRIX, modelMatrix);

            // Animation management.
            if (!entity->GetModelItem()->GetAnimations().empty() &&
                entity->GetAnimCurrentIndex() < entity->GetModelItem()->GetAnimations().size())
            {
                Animation anim = entity->GetModelItem()->GetAnimations()[entity->GetAnimCurrentIndex()];
                Frame frame = anim.GetFrames()[entity->GetAnimCurrentFrameIndex()];
                const glm::mat4* jointMatrices = &(frame.frameTransformations[0].jointMatrix);
                shader->SetUniform(UNIFORM_JOINTSMATRIX, frame.frameTransformations.size(), jointMatrices);

            }
        }


    };


}
