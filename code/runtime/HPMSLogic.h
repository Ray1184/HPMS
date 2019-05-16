/*!
 * File HPMSLogic.h
 */

#pragma once

#include <unordered_map>
#include <string>
#include "vm/LuaVM.h"
#include "input/KeyEvent.h"
#include "../core/CustomLogic.h"
#include "../core/Names.h"
#include "../core/Renderer.h"
#include "../core/CGAPIManager.h"
#include "GameState.h"
#include "states/R25DGameState.h"

#define CONFIG_SCRIPT "Config.lua"

namespace hpms
{
    class HPMSLogic : public CustomLogic
    {
    private:
        LuaVM* vm;
        Renderer* renderer;
        FrameBuffer* frameBuffer;
        std::unordered_map<std::string, bool> keyStatusMap;
        GameState* currentState;
        bool clear;
    public:
        HPMSLogic() : clear(false), currentState(nullptr)
        {
            vm = hpms::SafeNew<LuaVM>();
            renderer = CGAPIManager::Instance().CreateNewRenderer();
            int width = hpms::GetConf("WND_WIDTH", 320);
            int height = hpms::GetConf("WND_HEIGHT", 200);
            frameBuffer = CGAPIManager::Instance().CreateNewFrameBuffer(width, height);
        }

        ~HPMSLogic()
        {
            Cleanup();
        }

        inline void Init(Window* window) override
        {

            vm->RegisterAll();
            vm->ExecuteScript(std::string(SCRIPTS_FOLDER CONFIG_SCRIPT));
            LuaRef config = vm->GetGlobal("config");

            // TODO - Caching all buffered resources.

            std::string firstScript = config["first_script"];
            LoadState(firstScript);
        }

        inline void Input(Window* window) override
        {
            std::vector<KeyEvent> events;
            CheckKeyBehavior(window, events, KEY_W, "W");
            CheckKeyBehavior(window, events, KEY_A, "A");
            CheckKeyBehavior(window, events, KEY_S, "S");
            CheckKeyBehavior(window, events, KEY_D, "D");
            CheckKeyBehavior(window, events, KEY_Q, "Q");
            CheckKeyBehavior(window, events, KEY_I, "I");
            CheckKeyBehavior(window, events, KEY_P, "P");
            CheckKeyBehavior(window, events, KEY_E, "E");
            CheckKeyBehavior(window, events, KEY_SPACE, "SPACE");
            CheckKeyBehavior(window, events, KEY_ENTER, "ENTER");
            CheckKeyBehavior(window, events, KEY_ESCAPE, "ESC");
            CheckKeyBehavior(window, events, KEY_UP, "UP");
            CheckKeyBehavior(window, events, KEY_DOWN, "DOWN");
            CheckKeyBehavior(window, events, KEY_LEFT, "LEFT");
            CheckKeyBehavior(window, events, KEY_RIGHT, "RIGHT");
            currentState->Input(events);
        }

        inline void Update(Window* window) override
        {
            if (currentState->GetStatus() == hpms::Status::NEW)
            {
                currentState->Init();
                currentState->GetPipeline()->Init(window, currentState->GetScene(), renderer, frameBuffer);
                currentState->SetStatus(Status::RUNNING);
            } else if (currentState->GetStatus() == Status::RUNNING)
            {
                currentState->Update();
            } else
            {
                currentState->GetPipeline()->Cleanup(currentState->GetScene(), renderer, frameBuffer);
                currentState->Cleanup();
                std::string nextScript = currentState->GetStateToSwitch();
                hpms::SafeDelete(currentState);
                LoadState(nextScript);
            }
        }

        inline void Render(Window* window) override
        {
            currentState->GetPipeline()->Render(window, currentState->GetScene(), currentState->GetCamera(), renderer,
                                                frameBuffer);
        }

        inline void Cleanup() override
        {
            if (!clear)
            {
                clear = true;
                CGAPIManager::Instance().FreeFrameBuffer();
                CGAPIManager::Instance().FreeRenderer();
                ResourceCache::Instance().FreeAll();
                hpms::SafeDelete(vm);

            }
        }

        inline bool Quit() override
        {
            if (currentState->Quit())
            {
                currentState->GetPipeline()->Cleanup(currentState->GetScene(), renderer, frameBuffer);
                hpms::SafeDelete(currentState);
                return true;
            }
            return false;
        }

        inline void CheckKeyBehavior(Window* window, std::vector<KeyEvent>& events, unsigned int keyCode,
                                     const std::string& keyChar)
        {
            if (window->KeyPressed(keyCode))
            {
                KeyEvent event;
                event.key = keyChar;
                if (!keyStatusMap[keyChar])
                {
                    event.inputType = KeyEvent::PRESSED_FIRST_TIME;
                    keyStatusMap[keyChar] = true;
                } else
                {
                    event.inputType = KeyEvent::PRESSED;
                }
                events.push_back(event);
            } else if (window->KeyRelease(keyCode) && keyStatusMap[keyChar])
            {
                KeyEvent event;
                event.key = keyChar;
                event.inputType = KeyEvent::RELEASED;
                keyStatusMap[keyChar] = false;
                events.push_back(event);
            }
        }

        inline void LoadState(const std::string& script)
        {
            vm->ExecuteScript(std::string(SCRIPTS_FOLDER + script));
            LuaRef scene = vm->GetGlobal("scene");
            std::string mode = scene["mode"];
            if (mode.compare("R25D") == 0)
            {
                currentState = hpms::SafeNew<R25DGameState>(vm);
            } else
            {
                std::stringstream ss;
                ss << "State mode " << mode << " is not currently supported.";
                LOG_ERROR(ss.str().c_str());
            }
        }

        inline const std::string Name() const override
        {
            return "HPMSLogic";
        }


    };
}
