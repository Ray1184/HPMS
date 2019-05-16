/*!
 * File Window.h
 */

#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../common/HPMSObject.h"

namespace hpms
{
    struct Options : public HPMSObject
    {
        bool cullFace;
        bool showTriangles;
        bool showFps;
        bool compatibleProfile;
        bool fullscreen;

        Options()
        {}

        Options(bool cullFace, bool showTriangles, bool showFps, bool compatibleProfile,
                bool fullscreen) : cullFace(cullFace), showTriangles(showTriangles), showFps(showFps),
                                   compatibleProfile(compatibleProfile), fullscreen(fullscreen)
        {}

        inline const std::string Name() const override
        {
            return "Options";
        }

    };

    struct Perspective : public HPMSObject
    {
        float fov;
        float zNear;
        float zFar;

        Perspective()
        {}

        Perspective(float fov, float zNear, float zFar) : fov(fov), zNear(zNear), zFar(zFar)
        {}

        inline const std::string Name() const override
        {
            return "Perspective";
        }
    };


    class Window : public HPMSObject
    {
    public:


        virtual glm::mat4& UpdateProjectionMatrix() = 0;

        virtual void Init() = 0;

        virtual void Update() = 0;

        virtual bool KeyPressed(int keyCode) = 0;

        virtual bool KeyRelease(int keyCode) = 0;

        virtual void ChangeTitle(const std::string& title) = 0;

        virtual const std::string& GetTitle() const = 0;

        virtual unsigned int GetWidth() const = 0;

        virtual unsigned int GetHeight() const = 0;

        virtual bool IsVSync() const = 0;

        virtual void* GetWindow() const = 0;

        virtual const glm::mat4& GetProjMatrix() const = 0;

        virtual const Options& GetOptions() const = 0;

        virtual const Perspective& GetPerspective() const = 0;


    };
}