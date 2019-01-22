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

        virtual void QuadMeshInit() = 0;

        virtual void MeshInit(hpms::Mesh& mesh) = 0;

        virtual void
        ModelsDraw(std::unordered_map<Mesh, std::vector<Entity*>, MeshHasher, MeshEqual> meshesToEntitiesMap, Shader* s,
                   std::function<void(Entity*, Shader*)> pipelineCallback) = 0;

        virtual void QuadsDraw(const std::string& textureName) = 0;

        virtual void MeshCleanup(hpms::Mesh& mesh) = 0;

        virtual void TextureInit(hpms::Texture& text) = 0;

        virtual void TextureCleanup(hpms::Texture& text) = 0;

        virtual void QuadMeshCleanup() = 0;

        virtual void ClearBuffer() = 0;

    };
}
