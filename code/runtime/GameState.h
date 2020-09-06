#include <utility>

/*!
 * File GameState.h
 */

#pragma once

#include <string>
#include <vector>
#include "../core/Window.h"
#include "../core/Renderer.h"
#include "../core/Scene.h"
#include "../core/Pipeline.h"
#include "input/KeyEvent.h"
#include "HPMSLogic.h"

namespace hpms
{

    enum Status
    {
        NEW = 0,
        RUNNING = 1,
        FINISHED = 2
    };

    class GameState : public HPMSObject
    {
    protected:
        Scene* scene;
        Camera* camera;
        Pipeline* pipeline;
        Status status;
        std::string stateToSwitch;
        LuaVM* vm;
        bool clear;
    public:


        explicit GameState(LuaVM* pvm) : vm(pvm), clear(false)
        {
            status = NEW;
            scene = hpms::SafeNew<Scene>();
            camera = hpms::SafeNew<Camera>();
        }

        virtual ~GameState()
        {
            Cleanup();
        }

        void Init()
        {
            LuaRef sceneFun = vm->GetGlobal("scene");
            LuaRef initFunc = sceneFun["setup"];
            initFunc(scene, camera);
            CInit();
        }

        void Update()
        {
            LuaRef sceneFun = vm->GetGlobal("scene");
            LuaRef updateFunc = sceneFun["update"];
            updateFunc(scene, camera);
            CUpdate();
        }

        void Cleanup()
        {
            if (!clear)
            {
                clear = true;
                hpms::SafeDelete(scene);
                hpms::SafeDelete(camera);
                LuaRef sceneFun = vm->GetGlobal("scene");
                LuaRef cleanup = sceneFun["cleanup"];
                cleanup();
            }
        }


        void Input(std::vector<KeyEvent>& events)
        {
            LuaRef sceneFun = vm->GetGlobal("scene");
            LuaRef inputFunc = sceneFun["input"];
            inputFunc(&events);
        }

        bool Quit()
        {
            LuaRef scene = vm->GetGlobal("scene");
            bool quit = scene["quit"];
            return quit;
        }

        virtual void CInit() = 0;

        virtual void CUpdate() = 0;

        virtual void CCleanup() = 0;


        inline Status GetStatus() const
        {
            return status;
        }

        inline void SetStatus(Status status)
        {
            GameState::status = status;
        }

        inline Scene* GetScene() const
        {
            return scene;
        }


        inline Camera* GetCamera() const
        {
            return camera;
        }


        inline Pipeline* GetPipeline() const
        {
            return pipeline;
        }


        inline const std::string& GetStateToSwitch() const
        {
            return stateToSwitch;
        }

        inline void SetStateToSwitch(const std::string& stateToSwitch)
        {
            GameState::stateToSwitch = stateToSwitch;
        }
    };
}
