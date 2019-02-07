/*!
 * File AssimpImporter.h
 */

#include "AssimpImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

static glm::mat4 AIToGLMMat4(aiMatrix4x4 ai_mat)
{
    glm::mat4 result;

    aiMatrix4x4 transposed = ai_mat.Transpose();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i][j] = transposed[i][j];
        }
    }
    return result;
}

hpms::AdvModelItem* hpms::AssimpImporter::LoadModelItem(std::string& path, std::string& textDirs)
{
    AdvModelItem* advModelItem = hpms::SafeNew<AdvModelItem>();
    Assimp::Importer importer;
    const aiScene* aiScene = importer.ReadFile(path, aiProcess_GenSmoothNormals
                                                     | aiProcess_JoinIdenticalVertices
                                                     | aiProcess_Triangulate
                                                     | aiProcess_FixInfacingNormals
                                                     | aiProcess_LimitBoneWeights);

    if (aiScene == NULL)
    {
        std::stringstream ss;
        ss << "Error importing scene from " << path << std::endl;
        LOG_ERROR(ss.str().c_str());
        hpms::SafeDelete(advModelItem);
        return nullptr;
    }

    // Processing each material
    unsigned int numMaterials = aiScene->mNumMaterials;
    aiMaterial** aiMats = aiScene->mMaterials;
    std::vector<Material> materials;
    std::vector<Bone> bones;
    for (size_t i = 0; i < numMaterials; i++)
    {
        ProcessMaterial(aiMats[i], materials, textDirs);
    }

    // Processing each mesh
    unsigned int numMeshes = aiScene->mNumMeshes;
    aiMesh** aiMesh = aiScene->mMeshes;
    std::vector<Mesh> meshes;

    for (size_t i = 0; i < numMeshes; i++)
    {
        ProcessMesh(aiMesh[i], meshes, materials, bones);
    }

    // Process animations
    aiNode* aiRootNode = aiScene->mRootNode;
    glm::mat4 rootTransform = AIToGLMMat4(aiRootNode->mTransformation);
    AnimNode* rootAnimNode = ProcessGraph(aiRootNode, nullptr);
    std::vector<Animation> animations;
    ProcessAnimations(aiScene, bones, rootAnimNode, rootTransform, animations);
    hpms::SafeDelete(rootAnimNode);
    advModelItem->SetMeshes(meshes);
    advModelItem->SetAnimations(animations);
    return advModelItem;
}

void
hpms::AssimpImporter::ProcessMaterial(aiMaterial* aiMat, std::vector<hpms::Material>& materials,
                                      std::string& textDirs)
{
    Material material;
    if (aiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString path;

        if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
        {
            std::string innerPath(path.C_Str());
            if (innerPath.substr(0, 2) == ".\\")
            {
                innerPath = innerPath.substr(2, innerPath.size() - 2);
            }

            std::stringstream ss;
            ss << textDirs << "/" << innerPath;
            std::string textPath = ss.str();
            material.SetTextureName(textPath);
        }
    } else
    {
        std::string empty("");
        material.SetTextureName(empty);
    }
    aiColor4D color(0.0, 0.0, 0.0, 0.0);

    aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_AMBIENT, &color);
    glm::vec4 ambient = glm::vec4(color.r, color.g, color.b, color.a);
    material.SetAmbient(ambient);

    aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &color);
    glm::vec4 diffuse = glm::vec4(color.r, color.g, color.b, color.a);
    material.SetDiffuse(diffuse);

    materials.push_back(material);
}

void hpms::AssimpImporter::ProcessMesh(aiMesh* aiMesh, std::vector<hpms::Mesh>& meshes,
                                       std::vector<hpms::Material>& materials,
                                       std::vector<Bone>& bones)
{
    std::vector<float> positions;
    std::vector<float> textCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> jointIndices;
    std::vector<float> weights;
    bool textured = false;

    // Process vertices
    for (size_t i = 0; i < aiMesh->mNumVertices; i++)
    {
        // Positions
        if (aiMesh->HasPositions())
        {
            aiVector3D aiPos = aiMesh->mVertices[i];
            positions.push_back(aiPos.x);
            positions.push_back(aiPos.y);
            positions.push_back(aiPos.z);
        }

        // Text coords
        if (aiMesh->HasTextureCoords(0))
        {
            aiVector3D aiUv = aiMesh->mTextureCoords[0][i];
            textCoords.push_back(aiUv.x);
            textCoords.push_back(1 - aiUv.y);
            textured = true;
        }

        // Positions
        if (aiMesh->HasNormals())
        {
            aiVector3D aiNor = aiMesh->mNormals[i];
            normals.push_back(aiNor.x);
            normals.push_back(aiNor.y);
            normals.push_back(aiNor.z);
        }
    }

    // Process faces
    for (size_t i = 0; i < aiMesh->mNumFaces; i++)
    {
        if (aiMesh->HasFaces())
        {
            aiFace aiFace = aiMesh->mFaces[i];
            for (size_t j = 0; j < aiFace.mNumIndices; j++)
            {
                indices.push_back(aiFace.mIndices[j]);
            }
        }
    }

    // Process bones
    if (aiMesh->HasBones())
    {
        std::unordered_map<unsigned int, std::vector<VertexWeight>> weightSet;
        for (size_t i = 0; i < aiMesh->mNumBones; i++)
        {
            aiBone* aiBone = aiMesh->mBones[i];
            unsigned int id = bones.size();
            Bone bone{id, aiBone->mName.data, AIToGLMMat4(aiBone->mOffsetMatrix)};
            bones.push_back(bone);
            unsigned int numWeights = aiBone->mNumWeights;
            for (int j = 0; j < numWeights; j++)
            {
                aiVertexWeight aiWeight = aiBone->mWeights[j];
                VertexWeight vertexWeight{bone.boneId, aiWeight.mVertexId, aiWeight.mWeight};
                weightSet[vertexWeight.vertexId].push_back(vertexWeight);
            }
        }

        // Binding bones and vertex
        for (size_t i = 0; i < aiMesh->mNumVertices; i++)
        {

            size_t size;
            if (weightSet.find(i) == weightSet.end())
            {
                size = 0;
            } else
            {
                size = weightSet[i].size();
            }
            for (int j = 0; j < MAX_WEIGHTS; j++)
            {
                if (j < size)
                {
                    VertexWeight vw = weightSet[i][j];
                    weights.push_back(vw.weight);
                    jointIndices.push_back(vw.boneId);
                } else
                {
                    weights.push_back(0);
                    jointIndices.push_back(0);
                }
            }

        }
    }

    float boundingRad = 0.0f;
    for (float p : positions)
    {
        boundingRad = std::max(std::abs(p), boundingRad);
    }

    // Assemble mesh
    Mesh mesh;
    mesh.SetPositions(positions);
    mesh.SetNormals(normals);
    mesh.SetTextCoords(textCoords);
    mesh.SetIndices(indices);
    mesh.SetJointIndices(jointIndices);
    mesh.SetWeights(weights);
    mesh.SetVertexCount(indices.size());
    mesh.SetBoundingRadious(boundingRad);



    Material material;
    unsigned int materialIdx = aiMesh->mMaterialIndex;
    if (materialIdx >= 0 && materialIdx < materials.size())
    {
        material = materials.at(materialIdx);
    }
    mesh.SetMaterial(material);
    char buffer[32];
    hpms::RandomString(buffer, 32);
    std::stringstream ss;
    ss << aiMesh->mName.data << "_" << buffer;
    mesh.SetKey(ss.str());
    mesh.SetName(aiMesh->mName.data);
    meshes.push_back(mesh);


}

void hpms::AssimpImporter::BuildAnimationFrames(std::vector<hpms::Bone>& bones, hpms::AnimNode* animRootNode,
                                                glm::mat4 rootTransform, std::vector<hpms::Frame>& animationFrames)
{
    unsigned int numFrames = GetAnimationFrames(animRootNode);
    for (int i = 0; i < numFrames; i++)
    {
        Frame animatedFrame;
        unsigned int numBones = bones.size();
        for (int j = 0; j < numBones; j++)
        {
            Bone bone = bones.at(j);
            AnimNode* animNode = Find(bone.boneName, animRootNode);
            glm::mat4 boneMatrix = GetParentTransforms(animNode, i);
            boneMatrix = rootTransform * boneMatrix * bone.offsetMatrix;

            FrameTransform frameTransform{boneMatrix};


            animatedFrame.frameTransformations.push_back(frameTransform);
        }
        animationFrames.push_back(animatedFrame);
    }


}

void
hpms::AssimpImporter::ProcessAnimations(const aiScene* aiScen, std::vector<hpms::Bone>& bones, hpms::AnimNode* rootNode,
                                        glm::mat4 rootTransform,
                                        std::vector<hpms::Animation>& animations)
{
    int numAnimations = aiScen->mNumAnimations;
    for (int i = 0; i < numAnimations; i++)
    {
        aiAnimation* aiAnim = aiScen->mAnimations[i];
        unsigned int numChannels = aiAnim->mNumChannels;
        for (int j = 0; j < numChannels; j++)
        {
            aiNodeAnim* aiNodAn = aiAnim->mChannels[j];
            std::string nodeName = aiNodAn->mNodeName.data;
            AnimNode* animNode = Find(nodeName, rootNode);
            BuildTransFormationMatrices(aiNodAn, animNode);
        }
        std::vector<Frame> frames;
        BuildAnimationFrames(bones, rootNode, rootTransform, frames);
        Animation anim(aiAnim->mName.data, frames, aiAnim->mDuration);
        animations.push_back(anim);
    }
}

