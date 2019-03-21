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

        inline void Init() override
        {

            if (!glfwInit())
            {
                LOG_ERROR("Unable to initialize GLFW.");
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            if (options.compatibleProfile)
            {
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            } else
            {
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            }


            if (width == 0 || height == 0)
            {
                width = 100;
                height = 100;
                glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
            }

            window = glfwCreateWindow(width, height, title.c_str(),
                                      options.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
            if (window == NULL)
            {
                LOG_ERROR("Unable to create GLFW window.");
                glfwTerminate();
            }


            glfwMakeContextCurrent(window);

            if (vSync)
            {
                glfwSwapInterval(1);
            }

            glfwShowWindow(window);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                LOG_ERROR("Unable to create GLAD loader.");
            }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);


            if (options.showTriangles)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }


            if (options.cullFace)
            {
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
            }

            LOG_DEBUG("OpenGL window module initialized.");

        }

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