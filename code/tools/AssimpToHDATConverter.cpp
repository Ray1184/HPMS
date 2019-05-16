/*!
 * File AssimpToHDATConverterMain.h
 */

#include <string>
#include <iostream>
#include "AssimpImporter.h"
#include "../common/FileSystem.h"
#include "../core/ResourceCache.h"

int Serialize(std::string& filename, std::string& texPath, std::string& outPath);

int main(int argc, char** argv)
{
    if (argc < 3 || argc > 4)
    {
        std::cerr << "Arguments number " << argc - 1 << ", expected 2 or 3" << std::endl;
        return -1;
    }

    std::string outPath(argv[1]);
    std::string modelPath(argv[2]);
    std::string texPath("");
    if (argc == 4)
    {
        texPath = std::string(argv[3]);
    }

    std::cout << "Model path: " << modelPath << std::endl;
    std::cout << "Texture path: " << texPath << std::endl;
    std::cout << "Output path: " << outPath << std::endl;

    return Serialize(modelPath, texPath, outPath);

}

int Serialize(std::string& modelPath, std::string& texPath, std::string& outPath)
{
    hpms::AdvModelItem* item = hpms::AssimpImporter::LoadModelItem(modelPath, texPath);

    pods::ResizableOutputBuffer out;
    pods::BinarySerializer<decltype(out)> serializer(out);
    if (serializer.save(*item) != pods::Error::NoError)
    {
        std::cerr << "Error serializing " << modelPath << std::endl;
        hpms::SafeDelete(item);
        return -1;
    }

    std::ofstream outFile;
    outFile.open(outPath, std::ios::out | std::ios::binary);


    if (outFile.is_open())
    {
        outFile.write(out.data(), out.size());
    }

    outFile.close();
    std::cout << "Serialization completed successfully" << std::endl;
    hpms::SafeDelete(item);
    return 0;
}