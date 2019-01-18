/*!
 * File HPMSMainTest.h
 */

#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL


#include "../core/CustomLogic.h"
#include "../core/Simulator.h"
#include "../core/Renderer.h"
#include "../core/gl/GLRenderer.h"
#include "../core/Pipeline.h"
#include "../core/techniques/R25DPipeline.h"*/

using namespace hpms;


class TestLogic : public CustomLogic
{

public:
    virtual void Init(Window* window) override
    {
        renderer = new GLRenderer();
        pipeline = new R25DPipeline();
        scene = new Scene();

        AdvModelItem* testModel = ResourceCache::Instance().GetModel("data/out/01.hdat");


        testEntity = new Entity(testModel);
        testEntity->SetModelItem(testModel);
        testEntity->SetScale(glm::vec3(0.2, 0.2, 0.2));
        testEntity->SetPosition(glm::vec3(0, 0, 0));


        testEntity->SetRotation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
        scene->AddEntity(testEntity);
        scene->SetAmbientLight(glm::vec3(2, 2, 2));
        cam = new Camera();
        cam->SetPosition(glm::vec3(0, 2, 3));
        cam->SetRotation(glm::vec3(glm::radians(20.0), glm::radians(0.0), 0));
        cam->UpdateViewMatrix();
        pipeline->Init(window, scene, renderer);
        quit = false;

    }

    virtual void Input(Window* window) override
    {
        if (window->KeyPressed(GLFW_KEY_ESCAPE))
        {
            quit = true;
        }
    }

    virtual void Update() override
    {
        glm::quat rot = glm::rotate(testEntity->GetRotation(), 0.05f, glm::vec3(0.f, 1.f, 0.f));

        testEntity->SetRotation(rot);

        if (!testEntity->GetModelItem()->GetAnimations().empty())
        {
            if (testEntity->GetAnimCurrentFrameIndex() <
                testEntity->GetModelItem()->GetAnimations().at(0).GetFrames().size() - 1)
            {
                testEntity->SetAnimCurrentFrameIndex(testEntity->GetAnimCurrentFrameIndex() + 1);
            } else
            {
                testEntity->SetAnimCurrentFrameIndex(0);
            }
        }



    }


    virtual void Render(Window* window) override
    {

        pipeline->Render(window, scene, cam, renderer);
    }

    virtual void Cleanup() override
    {
        pipeline->Cleanup(scene, renderer);
        delete pipeline;
        delete renderer;

    }

    virtual bool Quit() override
    {
        return quit;
    }


private:


    Entity* testEntity;
    Renderer* renderer;
    Pipeline* pipeline;
    Scene* scene;
    Camera* cam;
    bool quit;

};


int SimulateNew();

int main()
{

    return SimulateNew();
}

int SimulateNew()
{
    Options opts;
    CustomLogic* logic = new TestLogic();
    opts.cullFace = true;
    opts.showFps = true;
    opts.compatibleProfile = false;
    opts.fullscreen = false;
    opts.showTriangles = false;
    Perspective pers;
    pers.fov = glm::radians(60.0);
    pers.zNear = 0.5;
    pers.zFar = 20;
    Simulator sim("HPMS Test", 320, 200, true, opts, pers, logic);
    sim.Start();
    return 0;
}

