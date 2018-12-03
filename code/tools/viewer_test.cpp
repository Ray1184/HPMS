#include <iostream>
#include "AssimpImporter.h"
#include "../core/AdvModelItem.h"
#include "../core/Mesh.h"
#define DATA_ARCHIVE "data/CrippleAnim2.zip"
#include "../common/FileSystem.h"
#include "../core/ResourceCache.h"
#include <fstream>
#include <pods/json.h>

void Serialize();
void Deserialize();

int main0() {
    Serialize();
    return 0;
}

void Deserialize() {

    //hpms::AdvModelItem* item = hpms::LoadBinResource<hpms::AdvModelItem>("CrippleAnim.json", &size);
    //std::cout << "Model loaded successfully." << std::endl;
    size_t size;
    hpms::Mesh* m = hpms::FileSystem::LoadBinResource<hpms::Mesh>("CrippleAnim.json", &size);
    //std::cout << "Num meshes: " <<  item->GetMeshes().size() << std::endl << std::endl;
    size_t count = 1;
    //for (const hpms::Mesh& m : item->GetMeshes()) {
        std::cout << "Mesh: " << count++ << std::endl;
        std::cout << "Mesh Name: " << m->GetName() << std::endl;
        std::cout << "Vertex Number: " << m->GetVertexCount() << std::endl;
        std::cout << "Material Texture: " << m->GetMaterial().GetTextureName() << std::endl << std::endl;

    //}
    /*std::cout << "Animations: " << item->GetAnimations().size() << std::endl << std::endl;
    for (hpms::Animation anim : item->GetAnimations())
    {

        std::cout << "Name: " << anim.GetName() << std::endl;
        std::cout << "Frames: " << anim.GetFrames().size() << std::endl;
        std::cout << "Duration: " << anim.GetDuration() << std::endl << std::endl;
    }*/
}
void Serialize() {


    // READ FROM ASSIMP
    std::string filename("data/resources/models/CrippleAnim.dae");
    std::string texPath("data/resources/textures");
    hpms::AdvModelItem* item = hpms::AssimpImporter::LoadModelItem(filename, texPath);


    // SERIALIZE
    pods::ResizableOutputBuffer out;
    pods::BinarySerializer<decltype(out)> serializer(out);
    if (serializer.save(*item) != pods::Error::NoError)
    {
        std::cerr << "Serialization error" << std::endl;
        return;
    }

    std::ofstream outFile;
    outFile.open("data/CrippleAnim2.hdat", std::ios::out | std::ios::binary);


    if (outFile.is_open())
    {
        outFile.write(out.data(), out.size());
    }

    outFile.close();

    // READ BINARY FROM CACHE

    hpms::AdvModelItem* itemR = hpms::ResourceCache::Instance().GetModel("CrippleAnim2.hdat");

    // RENDERING
    size_t count = 1;
    for (const hpms::Mesh& m : itemR->GetMeshes())
    {
        std::cout << "Mesh: " << count++ << std::endl;
        std::cout << "Mesh Name: " << m.GetName() << std::endl;
        std::cout << "Vertex Number: " << m.GetVertexCount() << std::endl;
    }


}