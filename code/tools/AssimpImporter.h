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
        unsigned int boneId;

        std::string boneName;

        glm::mat4 offsetMatrix;

    };

    struct VertexWeight
    {
        unsigned int boneId;

        unsigned int vertexId;

        float weight;
    };

    struct AnimNode
    {
        std::vector<AnimNode*> children;
        std::vector<glm::mat4> transformations;
        std::string name;
        AnimNode* parent;


        AnimNode(std::string pname, AnimNode* pparent) : name(pname), parent(pparent)
        {

        }

        ~AnimNode()
        {
            for (AnimNode* child : children)
            {
                delete child;
            }
        }


    };

    class AssimpImporter
    {
    public:
        static AdvModelItem* LoadModelItem(std::string& path, std::string& textDirs);

        static void DestroyModelItem(AdvModelItem*& modelItem)
        {
            hpms::SafeDelete(modelItem);
        }

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
                animNode->children.push_back(childAnimNode);
            }
            return animNode;
        }

        inline static AnimNode* Find(const std::string& name, AnimNode* parent)
        {
            AnimNode* res = nullptr;
            if (parent->name.compare(name) == 0)
            {
                res = parent;
            } else
            {
                for (AnimNode* child : parent->children)
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

            for (int i = 0; i < numFrames; i++) {
                aiVectorKey posKey = posKeys[i];
                aiVector3D vec = posKey.mValue;

                glm::mat4 transfMat(1.0);
                glm::translate(transfMat, glm::vec3(vec.x, vec.y, vec.z));

                aiQuatKey quatKey = rotKeys[i];
                aiQuaternion quat = quatKey.mValue;

                glm::quat rot(quat.w, quat.x, quat.y, quat.z);
                glm::mat4 rotMat = glm::mat4_cast(rot);
                // TODO - Check if traspose is needed.
                transfMat = transfMat * rotMat;

                if (i < aiNodAnim->mNumScalingKeys) {
                    posKey = scaleKeys[i];
                    vec = posKey.mValue;
                    transfMat = glm::scale(transfMat, glm::vec3(vec.x, vec.y, vec.z));
                }


                animNode->transformations.push_back(transfMat);
            }
        }

        inline static unsigned int GetAnimationFrames(AnimNode* parent)
        {
            unsigned int numFrames = parent->transformations.size();
            for (AnimNode* child : parent->children)
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
            glm::mat4 parentTransform = GetParentTransforms(node->parent, framePos);
            std::vector<glm::mat4> transformations = node->transformations;


            glm::mat4 nodeTransform(1.0);
            unsigned int transfSize = transformations.size();
            if (framePos < transfSize)
            {
                nodeTransform = transformations.at(framePos);
            } else if (transfSize > 0) {
                nodeTransform = transformations.at(transfSize - 1);
            }
            glm::mat4 res = parentTransform * nodeTransform;
            return res;
        }




    };
}


