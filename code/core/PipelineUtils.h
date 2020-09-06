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
#include "ResourceItemsCache.h"
#include "items/Picture.h"
#include "FrameBuffer.h"



namespace hpms
{
    class PipelineUtils
    {

    public:

        static Shader* Create3DSceneShader();

        static Shader* CreateFrameBufferShader(PostFX* postFx);

        static Shader* CreatePictureShader();

        static Shader* CreateDepthShader();

        static void
        RenderScene(Scene* scene, Window* window, Camera* camera, Shader* scene3DShader, Renderer* renderer, bool gui);

        static void RenderPictures(Scene* scene, Shader* pictureShader, Renderer* renderer, bool foreground);


        static void RenderDepthMask(Scene* scene, Window* window, Shader* depthShader, Renderer* renderer);

    private:

        static void RenderCallback(Entity* entity, Shader* shader, Camera* camera, Window* window);


    };


}
