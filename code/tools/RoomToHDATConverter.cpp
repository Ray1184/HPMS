/*!
 * File RoomToHDATConverterMain.h
 */

#include <string>
#include <sstream>
#include <iostream>
#include <pods/json.h>
#include <pods/buffers.h>
#include <pods/streams.h>
#include <fstream>
#include "../logic/RoomModelItem.h"
#include "RoomImporter.h"
#include "../common/FileSystem.h"



int Serialize(std::string& roomPath, std::string& outPath);


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Arguments number " << argc - 1 << ", expected 2" << std::endl;
        return -1;
    }

    std::string outPath(argv[1]);
    std::string roomPath(argv[2]);

    std::cout << "Room path: " << roomPath << std::endl;
    std::cout << "Output path: " << outPath << std::endl;


    return Serialize(roomPath, outPath);
}

int Serialize(std::string& roomPath, std::string& outPath)
{
    hpms::RoomModelItem* item = hpms::RoomImporter::LoadRoom(roomPath);
    pods::ResizableOutputBuffer out;
    pods::BinarySerializer<decltype(out)> serializer(out);
    if (serializer.save(*item) != pods::Error::NoError)
    {
        std::cerr << "Error serializing " << roomPath << std::endl;
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
