/**
 * File GLRenderer.h
 */
#pragma once

#include "../Renderer.h"
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

        void ModelsDraw(Mesh& mesh, Texture* texture, std::vector<hpms::AdvModelItem*>& items,
                        Transformation& t, Shader& s,
                        std::function<void(AdvModelItem*, Transformation&, Shader&)> pipelineCallback) override;

        void MeshCleanup(hpms::Mesh& mesh) override;

        void TextureInit(hpms::Texture& text) override;

        void TextureCleanup(hpms::Texture& text) override;

        void ClearBuffer() override;

    private:

        std::unordered_map<std::string, Texture> textureCache;

    };
}
