/**
 * File GLRenderer.h
 */
#pragma once

#include "../Renderer.h"
#include <glad/glad.h>
#include <unordered_map>

namespace hpms
{
    class GLRenderer : public Renderer
    {

    public:
        GLRenderer()
        {
            LOG_DEBUG("OpenGL rendering module created.");
        }

        void QuadMeshInit() override;

        void MeshInit(hpms::Mesh& mesh) override;

        void
        ModelsDraw(std::unordered_map<Mesh, std::vector<Entity*>, MeshHasher, MeshEqual> meshesToEntitiesMap, Shader* s,
                   std::function<void(Entity*, Shader*)> pipelineCallback) override;

        void QuadsDraw(const std::string& textureName) override;

        void MeshCleanup(hpms::Mesh& mesh) override;

        void TextureInit(hpms::Texture& text) override;

        void TextureCleanup(hpms::Texture& text) override;

        void QuadMeshCleanup() override;

        void ClearAllBuffers() override;

        void ClearDepthBuffer() override;

    private:

        GLuint quadVbo;

        GLuint quadVao;

        std::unordered_map<std::string, GLuint> vaoMap;

        std::unordered_map<std::string, GLuint> texBufferMap;

        std::unordered_map<std::string, std::vector<GLuint>> vbosMap;


    };
}
