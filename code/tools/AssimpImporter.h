/*!
 * File AssimpImporter.h
 */

#pragma once

#include <string>
#include <sstream>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "../core/StdModelItem.h"
#include "../core/AdvModelItem.h"
#include "../core/Material.h"
#include "../core/Mesh.h"
#include "../common/Utils.h"

#define MAX_WEIGHTS 4

namespace hpms
{

    struct Bone
    {
        size_t boneId;

        std::string boneName;

        glm::mat4 offsetMatrix;

        Bone()
        {}

        Bone(size_t boneId, const std::string& boneName, const glm::mat4& offsetMatrix) : boneId(boneId),
                                                                                          boneName(boneName),
                                                                                          offsetMatrix(offsetMatrix)
        {}


    };

    struct VertexWeight
    {
        unsigned int boneId;

        unsigned int vertexId;

        float weight;

        VertexWeight()
        {}

        VertexWeight(unsigned int boneId, unsigned int vertexId, float weight) : boneId(boneId), vertexId(vertexId),
                                                                                 weight(weight)
        {}


    };

    class AnimNode : public HPMSObject
    {
    private:
        std::vector<AnimNode*> children;
        std::vector<glm::mat4> transformations;
        std::string name;
        AnimNode* parent;

    public:


        AnimNode(std::string pname, AnimNode* pparent) : name(pname), parent(pparent)
        {

        }

        ~AnimNode()
        {
            for (AnimNode* child : children)
            {
                hpms::SafeDelete(child);
            }
        }

        inline void AddTransform(const glm::mat4 mat)
        {
            transformations.push_back(mat);
        }

        inline const std::vector<AnimNode*>& GetChildren() const
        {
            return children;
        }

        inline void AddChild(AnimNode* node)
        {
            children.push_back(node);
        }

        inline void SetChildren(const std::vector<AnimNode*>& children)
        {
            AnimNode::children = children;
        }

        inline const std::vector<glm::mat4>& GetTransformations() const
        {
            return transformations;
        }

        inline void SetTransformations(const std::vector<glm::mat4>& transformations)
        {
            AnimNode::transformations = transformations;
        }

        inline const std::string& GetName() const
        {
            return name;
        }

        inline void SetName(const std::string& name)
        {
            AnimNode::name = name;
        }

        inline AnimNode* GetParent() const
        {
            return parent;
        }

        inline void SetParent(AnimNode* parent)
        {
            AnimNode::parent = parent;
        }

        inline const std::string Name() const override
        {
            return "AnimNode";
        }


    };

    class AssimpImporter
    {
    public:
        static AdvModelItem* LoadModelItem(std::string& path, std::string& textDirs);


    private:
        static void ProcessMaterial(aiMaterial* aiMat, std::vector<Material>& materials, std::string& textDirs);

        static void ProcessMesh(aiMesh* aiMesh, std::vector<Mesh>& meshes, std::vector<Material>& materials,
                                std::vector<Bone>& bones);


        static void
        ProcessAnimations(const aiScene* aiScen, std::vector<Bone>& bones, AnimNode* rootNode, glm::mat4 rootTransform,
                          std::vector<hpms::Animation>& animations);

        static void BuildAnimationFrames(std::vector<Bone>& bones, AnimNode* animRootNode, glm::mat4 rootTransform,
                                         std::vector<hpms::Frame>& animationFrames);

        inline static AnimNode* ProcessGraph(aiNode* aiNod, AnimNode* parent)
        {
            std::string nodeName = aiNod->mName.data;
            //AnimNode* animNode = new AnimNode(nodeName, parent);
            AnimNode* animNode = hpms::SafeNew<AnimNode>(nodeName, parent);
            unsigned int numChildren = aiNod->mNumChildren;
            for (int i = 0; i < numChildren; i++)
            {
                aiNode* aiChildNod = aiNod->mChildren[i];
                AnimNode* childAnimNode = ProcessGraph(aiChildNod, animNode);
                animNode->AddChild(childAnimNode);
            }
            return animNode;
        }

        inline static AnimNode* Find(const std::string& name, AnimNode* parent)
        {
            AnimNode* res = nullptr;
            if (parent->GetName().compare(name) == 0)
            {
                res = parent;
            } else
            {
                for (AnimNode* child : parent->GetChildren())
                {
                    res = Find(name, child);
                    if (res != nullptr)
                    {
                        break;
                    }
                }
            }
            return res;
        }

        inline static void BuildTransFormationMatrices(aiNodeAnim* aiNodAnim, AnimNode* animNode)
        {
            unsigned int numFrames = aiNodAnim->mNumPositionKeys;

            aiVectorKey* posKeys = aiNodAnim->mPositionKeys;
            aiVectorKey* scaleKeys = aiNodAnim->mScalingKeys;
            aiQuatKey* rotKeys = aiNodAnim->mRotationKeys;

            for (int i = 0; i < numFrames; i++)
            {
                aiVectorKey posKey = posKeys[i];
                aiVector3D vec = posKey.mValue;

                glm::mat4 transfMat(1.0);
                transfMat = glm::translate(transfMat, glm::vec3(vec.x, vec.y, vec.z));

                aiQuatKey quatKey = rotKeys[i];
                aiQuaternion quat = quatKey.mValue;

                glm::quat rot(quat.w, quat.x, quat.y, quat.z);
                glm::mat4 rotMat = glm::mat4_cast(rot);
                transfMat = transfMat * rotMat;

                if (i < aiNodAnim->mNumScalingKeys)
                {
                    posKey = scaleKeys[i];
                    vec = posKey.mValue;
                    transfMat = glm::scale(transfMat, glm::vec3(vec.x, vec.y, vec.z));
                }


                animNode->AddTransform(transfMat);
            }
        }

        inline static unsigned int GetAnimationFrames(AnimNode* parent)
        {
            unsigned int numFrames = parent->GetTransformations().size();
            for (AnimNode* child : parent->GetChildren())
            {
                unsigned int childFrames = GetAnimationFrames(child);
                numFrames = std::max(numFrames, childFrames);
            }
            return numFrames;
        }


        inline static glm::mat4 GetParentTransforms(AnimNode* node, unsigned int framePos)
        {
            if (node == nullptr)
            {
                return glm::mat4(1.0);

            }
            glm::mat4 parentTransform = GetParentTransforms(node->GetParent(), framePos);
            std::vector<glm::mat4> transformations = node->GetTransformations();


            glm::mat4 nodeTransform(1.0);
            unsigned int transfSize = transformations.size();
            if (framePos < transfSize)
            {
                nodeTransform = transformations.at(framePos);
            } else if (transfSize > 0)
            {
                nodeTransform = transformations.at(transfSize - 1);
            }
            glm::mat4 res = parentTransform * nodeTransform;
            return res;
        }


    };
}


