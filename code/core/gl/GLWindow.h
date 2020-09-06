/*!
 * File GLWindow.h
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../common/Utils.h"
#include "../Window.h"

namespace hpms
{

    class GLWindow : public hpms::Window
    {
    public:
        GLWindow(const std::string& ptitle, const unsigned int pwidth, const unsigned int pheight,
                 const bool pvSync, const Options& poptions, const Perspective& pperspective) :
                title(ptitle),
                width(pwidth),
                height(pheight),
                vSync(pvSync),
                options(poptions),
                perspective(pperspective),
                projMatrix(glm::mat4(1.0))
        {
            LOG_DEBUG("OpenGL window module created.");
        }


        inline glm::mat4& UpdateProjectionMatrix() override
        {
            float aspectRatio = (float) width / (float) height;
            projMatrix = glm::perspective(perspective.fov, aspectRatio, perspective.zNear, perspective.zFar);
            return projMatrix;
        }

        void Init() override;

        inline void Update() override
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        inline bool KeyPressed(int keyCode) override
        {
            return glfwGetKey(window, keyCode) == GLFW_PRESS;
        }


        inline bool KeyRelease(int keyCode) override
        {
            return glfwGetKey(window, keyCode) == GLFW_RELEASE;
        }

        inline void ChangeTitle(const std::string& title) override
        {
            glfwSetWindowTitle(window, title.c_str());
        }

        inline const std::string& GetTitle() const override
        {
            return title;
        }

        inline unsigned int GetWidth() const override
        {
            return width;
        }

        inline unsigned int GetHeight() const override
        {
            return height;
        }

        inline bool IsVSync() const override
        {
            return vSync;
        }

        inline void* GetWindow() const override
        {
            return window;
        }

        inline const glm::mat4& GetProjMatrix() const override
        {
            return projMatrix;
        }

        inline const Options& GetOptions() const override
        {
            return options;
        }

        inline const Perspective& GetPerspective() const override
        {
            return perspective;
        }

        inline const std::string Name() const override
        {
            return "GLWindow";
        }

    private:

        std::string title;
        unsigned int width;
        unsigned int height;
        bool vSync;
        GLFWwindow* window;
        glm::mat4 projMatrix;
        Options options;
        Perspective perspective;

    };
}