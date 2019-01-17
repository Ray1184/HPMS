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

        void MeshInit(hpms::Mesh& mesh) override;

        void ModelsDraw(Mesh& mesh, Texture* texture, const AdvModelItem* currentItem, const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& itemsMap,
                        Shader* s, std::function<void(const AdvModelItem*, Entity*, Shader*)> pipelineCallback) override;

        void MeshCleanup(hpms::Mesh& mesh) override;

        void TextureInit(hpms::Texture& text) override;

        void TextureCleanup(hpms::Texture& text) override;

        void ClearBuffer() override;

    private:

        std::unordered_map<std::string, GLuint> vaoMap;

        std::unordered_map<std::string, std::vector<GLuint>> vbosMap;

    };
}
