/*!
 * File Simulator.h
 */

#pragma once

#include <string>
#include <chrono>
#include <thread>
#include "Window.h"
#include "CustomLogic.h"
#include "../common/Utils.h"
#include "CGAPIManager.h"

#define TARGET_FPS 6000.0 // Frame per seconds.

// Dynamic updated disabled.
/*
#define TARGET_UPS 30.0 // Update per seconds.
 */

namespace hpms
{
    class Timer
    {
    public:
        Timer() : lastLoopTime(0.0)
        {

        }

        inline void Init()
        {
            lastLoopTime = GetTime();
        }

        inline double GetTime()
        {


            auto tse = std::chrono::system_clock::now().time_since_epoch();
            auto nowNs = std::chrono::duration_cast<std::chrono::nanoseconds>(tse);
            return nowNs.count() / 1000000000.0;

        }

        inline float UpdateElapsedTime()
        {
            double time = GetTime();
            float elapsedTime = (float) (time - lastLoopTime);
            lastLoopTime = time;
            return elapsedTime;
        }

        inline double GetLastLoopTime() const
        {
            return lastLoopTime;
        }

    private:
        double lastLoopTime;
        std::chrono::high_resolution_clock clock;


    };

    class Simulator
    {
    public:
        Simulator(const std::string& ptitle, unsigned int width, unsigned int height, bool vSync, Options& options,
                  Perspective& perspective, CustomLogic* plogic) :
                title(ptitle),
                logic(plogic),
                lastFps(0.0),
                fps(0)
        {
            window = CGAPIManager::Instance().CreateNewWindow(ptitle, width, height, vSync, options, perspective);
            logic = plogic;
            LOG_DEBUG("Simulator module created.");
        }


        inline void Start()
        {
            Init();
            Loop();
        }


    private:
        Window* window;
        CustomLogic* logic;
        std::string title;
        double lastFps;
        int fps;
        Timer timer;

        inline void Init()
        {
            window->Init();
            timer.Init();
            logic->Init(window);
            lastFps = timer.GetTime();
            fps = 0;
            LOG_DEBUG("Simulator module initialized.");
        }

        inline void Loop()
        {
            // Dynamic updated disabled.
            /*
            float elapsedTime;
            float accumulator = 0;
            float interval = 1.0 / TARGET_UPS;
             */

            LOG_DEBUG("Main loop started.");
            while (!logic->Quit())
            {


                // Dynamic updated disabled.
                /*
                elapsedTime = timer.UpdateElapsedTime();
                accumulator += elapsedTime;
                 */

                timer.UpdateElapsedTime();
                Input();
                Update();

                // Dynamic updated disabled.
                /*
                while (accumulator >= interval) {
                    UpdateRealTime(interval);
                    accumulator -= interval;
                }
                 */

                Render();

                if (!window->IsVSync())
                {
                    //Sync();
                }
            }
            LOG_DEBUG("Main loop stopped.");
            Cleanup();
        }

        inline void Cleanup()
        {
            CGAPIManager::Instance().FreeWindow();
            logic->Cleanup();
            hpms::SafeDelete(logic);
            LOG_DEBUG("Simulator module cleanup done.");
        }

        inline void Sync()
        {
            float loopSlot = 1 / TARGET_FPS;
            double endTime = timer.GetLastLoopTime() + loopSlot;
            while (timer.GetTime() < endTime)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        inline void Input()
        {
            logic->Input(window);
        }

        inline void Update()
        {
            logic->Update();
        }

        // Dynamic updated disabled.
        /*
        inline void UpdateRealTime(float fps)
        {
            logic->UpdateRealTime(fps);
        }
         */

        inline void Render()
        {
            if (window->GetOptions().showFps)
            {
                fps++;
                double currentFps = timer.GetLastLoopTime();
                if (currentFps - lastFps > 1)
                {

                    lastFps = timer.GetLastLoopTime();
                    std::stringstream ss;
                    ss << window->GetTitle() << " - " << fps << " FPS";
                    window->ChangeTitle(ss.str());
                    fps = 0;
                }
            }
            logic->Render(window);
            window->Update();
        }
    };
}
