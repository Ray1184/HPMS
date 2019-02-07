/*!
 * File Mesh.h
 */

#pragma once

#include <vector>
#include <string>
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
        float boundingRadious;
        unsigned int textured; // Type bool cannot be serialized, use uint instead.
        Material material;
        std::string name;
        unsigned int vertexCount;
        std::string key;


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
                PODS_OPT(vertexCount),
                PODS_OPT(key),
                PODS_OPT(boundingRadious)
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

        inline const std::string& GetKey() const
        {
            return key;
        }

        inline void SetKey(const std::string& key)
        {
            Mesh::key = key;
        }

        inline bool operator==(const Mesh& rhs) const
        {
            return key.compare(rhs.GetKey()) == 0;
        }

        inline bool operator!=(const Mesh& rhs) const
        {
            return !(rhs == *this);
        }

        inline float GetBoundingRadious() const
        {
            return boundingRadious;
        }

        inline void SetBoundingRadious(float boundingRadious)
        {
            Mesh::boundingRadious = boundingRadious;
        }
    };

}
