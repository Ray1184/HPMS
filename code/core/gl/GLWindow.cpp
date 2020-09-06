/*!
 * File GLWindow.cpp
 */

#include "GLWindow.h"

void hpms::GLWindow::Init()
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

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
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

