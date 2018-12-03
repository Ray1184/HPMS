/*!
 * File Mesh.h
 */

#pragma once

#include <glad/glad.h>
#include <vector>
#include "Material.h"
#include <pods/pods.h>
#include <pods/buffers.h>
#include <pods/binary.h>

namespace hpms
{


    class Mesh
    {
    private:


        std::vector<float> positions;
        std::vector<float> textCoords;
        std::vector<float> normals;
        std::vector<unsigned int> indices;
        std::vector<unsigned int> jointIndices;
        std::vector<float> weights;
        unsigned int textured; // Type bool cannot be serialized, use uint instead.
        Material material;
        std::string name;
        unsigned int vertexCount;


        // Transient data.
        unsigned int vaoId;
        std::vector<unsigned int> vboList;

    public:


        PODS_SERIALIZABLE(
                1,
                PODS_OPT(positions),
                PODS_OPT(textCoords),
                PODS_OPT(normals),
                PODS_OPT(indices),
                PODS_OPT(jointIndices),
                PODS_OPT(weights),
                PODS_OPT(textured),
                PODS_OPT(material),
                PODS_OPT(name),
                PODS_OPT(vertexCount)
        )

        inline const std::vector<float>& GetPositions() const
        {
            return positions;
        }

        inline void SetPositions(const std::vector<float>& positions)
        {
            Mesh::positions = positions;
        }

        inline const std::vector<float>& GetTextCoords() const
        {
            return textCoords;
        }

        inline void SetTextCoords(const std::vector<float>& textCoords)
        {
            Mesh::textCoords = textCoords;
        }

        inline const std::vector<float>& GetNormals() const
        {
            return normals;
        }

        inline void SetNormals(const std::vector<float>& normals)
        {
            Mesh::normals = normals;
        }

        inline const std::vector<unsigned int>& GetIndices() const
        {
            return indices;
        }

        inline void SetIndices(const std::vector<unsigned int>& indices)
        {
            Mesh::indices = indices;
        }

        inline const std::vector<unsigned int>& GetJointIndices() const
        {
            return jointIndices;
        }

        inline void SetJointIndices(const std::vector<unsigned int>& jointIndices)
        {
            Mesh::jointIndices = jointIndices;
        }

        inline const std::vector<float>& GetWeights() const
        {
            return weights;
        }

        inline void SetWeights(const std::vector<float>& weights)
        {
            Mesh::weights = weights;
        }


        inline unsigned int GetVaoId() const
        {
            return vaoId;
        }

        inline void SetVaoId(unsigned int vaoId)
        {
            Mesh::vaoId = vaoId;
        }

        inline const std::vector<unsigned int>& GetVboList() const
        {
            return vboList;
        }

        inline void AddVbo(unsigned int vbo)
        {
            vboList.push_back(vbo);
        }

        inline unsigned int GetVertexCount() const
        {
            return vertexCount;
        }

        inline void SetVertexCount(unsigned int vertexCount)
        {
            Mesh::vertexCount = vertexCount;
        }

        inline bool IsTextured() const
        {
            return textured && !material.GetTextureName().empty();
        }

        inline void SetTextured(bool textured)
        {
            Mesh::textured = textured;
        }

        inline const Material& GetMaterial() const
        {
            return material;
        }

        inline void SetMaterial(const Material& material)
        {
            Mesh::material = material;
        }

        inline const std::string& GetName() const
        {
            return name;
        }

        inline void SetName(const std::string& name)
        {
            Mesh::name = name;
        }
    };


    struct MeshHasher
    {
    public:
        size_t operator()(Mesh const key) const
        {

            size_t hash = 0;
            for (size_t i = 0; i < key.GetName().size(); i++)
            {
                hash ^= (71 * hash + key.GetName()[i]) % 5;
            }

            
            hash ^= key.GetPositions().size();
            hash ^= key.GetNormals().size();
            hash ^= key.GetTextCoords().size();
            hash ^= key.GetJointIndices().size();
            hash ^= key.GetWeights().size();
            hash ^= key.GetIndices().size();

            if (key.IsTextured())
            {
                for (size_t i = 0; i < key.GetMaterial().GetTextureName().size(); i++)
                {
                    hash ^= (71 * hash + key.GetMaterial().GetTextureName()[i]) % 5;
                }
            }
            return hash;
        }
    };

    // TODO - Enhance compare function.
    struct MeshEqualFn
    {

        bool operator()(Mesh const m1, Mesh const m2) const
        {
            return (m1.GetName().compare(m2.GetName()));
        }
    };
}
