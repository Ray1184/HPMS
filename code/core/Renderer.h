/**
 * File Renderer.h
 */
#pragma once

#include <vector>
#include <functional>
#include "Mesh.h"
#include "AdvModelItem.h"
#include "Texture.h"
#include "Transformation.h"
#include "Shader.h"
#include "Entity.h"


namespace hpms
{
    class Renderer
    {

    public:

        virtual void MeshInit(hpms::Mesh& mesh) = 0;

        virtual void
        ModelsDraw(Mesh& mesh, Texture* texture, const AdvModelItem* currentItem, const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& itemsMap,
                   Shader* s, std::function<void(const AdvModelItem*, Entity*, Shader*)> pipelineCallback) = 0;

        virtual void MeshCleanup(hpms::Mesh& mesh) = 0;

        virtual void TextureInit(hpms::Texture& text) = 0;

        virtual void TextureCleanup(hpms::Texture& text) = 0;

        virtual void ClearBuffer() = 0;

    };
}
