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

namespace hpms
{
    class PipelineUtils
    {

    public:

        inline static Shader* CreateSceneShader()
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

        inline static void RenderScene(Window* window, Camera* camera, Scene* scene,
                                       Shader* shader, bool gui, Renderer* renderer)
        {
            renderer->ClearBuffer();
            shader->Bind();


            glm::mat4 viewMatrix = camera->GetViewMatrix();
            glm::mat4 projMatrix = window->GetProjMatrix();

            shader->SetUniform(UNIFORM_VIEWMATRIX, viewMatrix);
            shader->SetUniform(UNIFORM_PROJMATRIX, projMatrix);
            shader->SetUniform(UNIFORM_DIFFUSEINTENSITY, gui ? 1.0f : 0.1f);
            shader->SetUniform(UNIFORM_AMBIENTLIGHT, scene->GetAmbientLight());
            shader->SetUniform(UNIFORM_TEXSAMPLER, 0);

            // Render pass.

            for (auto& entry : scene->GetModelsMap())
            {
                const AdvModelItem* item = entry.first;
                for (Mesh mesh : item->GetMeshes())
                {

                    shader->SetUniform(UNIFORM_MATERIAL, mesh.GetMaterial());
                    Texture* tex = nullptr;
                    if (mesh.IsTextured())
                    {
                        tex = ResourceCache::Instance().GetTexture(mesh.GetMaterial().GetTextureName());
                    }

                    renderer->ModelsDraw(mesh, tex, item, scene->GetModelsMap(), shader, RenderCallback);


                }
            }
            shader->Unbind();
        }

    private:
        inline static void RenderCallback(const AdvModelItem* modelItem, Entity* entity, Shader* shader)
        {

            glm::mat4 modelMatrix = Transformation::BuildModelMatrix(entity);
            shader->SetUniform(UNIFORM_MODELMATRIX, modelMatrix);

            // Animation management.
            if (!modelItem->GetAnimations().empty() &&
                    entity->GetAnimCurrentIndex() < modelItem->GetAnimations().size())
            {
                Animation anim = modelItem->GetAnimations()[entity->GetAnimCurrentIndex()];
                Frame frame = anim.GetFrames()[entity->GetAnimCurrentFrameIndex()];
                const glm::mat4* jointMatrices = &(frame.frameTransformations[0].jointMatrix);
                shader->SetUniform(UNIFORM_JOINTSMATRIX, frame.frameTransformations.size(), jointMatrices);

            }
        }


    };


}
