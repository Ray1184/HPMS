/**
 * File Renderer.h
 */
#pragma once

#include <vector>
#include "Mesh.h"
#include "AdvModelItem.h"
#include "Texture.h"
#include "Transformation.h"
#include "Shader.h"


namespace hpms
{
    class Renderer
    {

    public:

        virtual void MeshInit(hpms::Mesh& mesh) = 0;

        virtual void
        ModelsDraw(Mesh& mesh, Texture* texture, std::vector<hpms::AdvModelItem*>& items,
                   Transformation& t, Shader& s,
                   std::function<void(AdvModelItem*, Transformation&, Shader&)> pipelineCallback) = 0;

        virtual void MeshCleanup(hpms::Mesh& mesh) = 0;

        virtual void TextureInit(hpms::Texture& text) = 0;

        virtual void TextureCleanup(hpms::Texture& text) = 0;

        virtual void ClearBuffer() = 0;

    };
}
