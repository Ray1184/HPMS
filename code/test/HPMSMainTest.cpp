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
#include "../core/techniques/R25DPipeline.h"

using namespace hpms;


std::string PrintMatrix(glm::mat4& m)
{
    std::stringstream ss;
    ss << "[" << m[0][0] << "]" << "[" << m[0][1] << "]" << "[" << m[0][2] << "]" << "[" << m[0][3] << "]" << std::endl;
    ss << "[" << m[1][0] << "]" << "[" << m[1][1] << "]" << "[" << m[1][2] << "]" << "[" << m[1][3] << "]" << std::endl;
    ss << "[" << m[2][0] << "]" << "[" << m[2][1] << "]" << "[" << m[2][2] << "]" << "[" << m[2][3] << "]" << std::endl;
    ss << "[" << m[3][0] << "]" << "[" << m[3][1] << "]" << "[" << m[3][2] << "]" << "[" << m[3][3] << "]" << std::endl;
    return ss.str();
}

class TestLogic : public CustomLogic
{

public:
    virtual void Init(Window* window) override
    {
        renderer = new GLRenderer();
        pipeline = new R25DPipeline();

        testModel = ResourceCache::Instance().GetModel("data/out/01.hdat");
        testModel->SetCurrentAnimationIndex(0);
        testModel->SetScale(glm::vec3(1, 1, 1));
        testModel->SetPosition(glm::vec3(1, 1, 1));
        testModel->SetRotation(glm::quat());
        scene.AddModel(testModel);
        cam.SetPosition(glm::vec3(0, 0, 0));
        cam.SetRotation(glm::vec3(0, 0, 0));
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

    }

    /*
    virtual void UpdateRealTime(float tpf) override
    {

    }
     */
    virtual void Render(Window* window) override
    {

        pipeline->Render(window, scene, cam, renderer);
    }

    virtual void Cleanup() override
    {
        std::cout << "CLEANUP" << std::endl;
        pipeline->Cleanup(scene, renderer);
        delete pipeline;
        delete renderer;

    }

    virtual bool Quit() override
    {
        return quit;
    }


private:

    Renderer* renderer;
    Pipeline* pipeline;
    Scene scene;
    AdvModelItem* testModel;
    Camera cam;
    bool quit;

};


int main()
{
    Options opts;
    CustomLogic* logic = new TestLogic();
    opts.cullFace = true;
    opts.showFps = true;
    opts.compatibleProfile = false;
    opts.fullscreen = false;
    opts.antialiasing = false;
    opts.showTriangles = false;
    Perspective pers;
    pers.fov = 60;
    pers.zNear = 0.1;
    pers.zFar = 100;
    Simulator sim("HPMS Test", 320, 200, true, opts, pers, logic);
    sim.Start();
}