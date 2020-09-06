/*!
 * File GLFrameBuffer.cpp
 */

#include "GLFrameBuffer.h"

void hpms::GLFrameBuffer::Init()
{
    glGenFramebuffers(1, &fboId);
    if (!fboId)
    {
        LOG_ERROR("Error creating frame buffer object.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    glGenTextures(1, &textId);
    glBindTexture(GL_TEXTURE_2D, textId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width,
                 height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenRenderbuffers(1, &rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textId, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, buffers);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("Error initializing frame buffer object.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);

    static GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
    };

    // Positions.
    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind VBO and VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    initialized = true;
}

void hpms::GLFrameBuffer::PreRendering()
{
    if (postFx == nullptr)
    {
        LOG_ERROR("Post FX needed for frame buffer.");
    }


    glViewport(0, 0, (int) (width / postFx->GetRatio()),
               (int) (height / postFx->GetRatio()));
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void hpms::GLFrameBuffer::PostRendering()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, (int) (width * postFx->GetRatio()),
               (int) (height * postFx->GetRatio()));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (fboShader == nullptr)
    {
        LOG_ERROR("Default shader needed for frame buffer.");
    }
    fboShader->Bind();
    postFx->ProcessShader(fboShader, params);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textId);

    glBindVertexArray(quadVao);
    glEnableVertexAttribArray(0);

    // Draw the mesh.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Restore state.
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    fboShader->Unbind();

}

void hpms::GLFrameBuffer::Cleanup()
{

    if (!clear && initialized)
    {
        clear = true;
        initialized = false;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteRenderbuffers(1, &rboId);
        glDeleteBuffers(1, &quadVbo);
        glDeleteTextures(1, &textId);
        glDeleteFramebuffers(1, &fboId);
        glDeleteVertexArrays(1, &vaoId);
    }

}
