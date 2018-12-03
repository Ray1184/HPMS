/*!
 * test_physfs.h
 */


#include <physfs/physfs.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <pods/pods.h>
#include <pods/buffers.h>
#include <pods/binary.h>
#include <fstream>
#include "common/filesystem.h"
#include <glm/glm.hpp>
#include <sstream>

std::string PrintMatrix(glm::mat4& m);

struct Server {
    std::string address = "localhost";  // this is default value
    uint16_t port = 8080;               // this is default value
    glm::mat4 m = glm::mat4(1.0);

    PODS_SERIALIZABLE(
            1,                      // this is version
            PODS_MDR(address),      // this field is mandatory
            PODS_OPT(port),
            PODS_OPT(m[0][0]),
            PODS_OPT(m[0][1]),
            PODS_OPT(m[0][2]),
            PODS_OPT(m[0][3]),
            PODS_OPT(m[1][0]),
            PODS_OPT(m[1][1]),
            PODS_OPT(m[1][2]),
            PODS_OPT(m[1][3]),
            PODS_OPT(m[2][0]),
            PODS_OPT(m[2][1]),
            PODS_OPT(m[2][2]),
            PODS_OPT(m[2][3]),
            PODS_OPT(m[3][0]),
            PODS_OPT(m[3][1]),
            PODS_OPT(m[3][2]),
            PODS_OPT(m[3][3])
    )
};

struct ServerList {
    std::vector<Server> servers =
            {
                    // this is default values
                    Server{"localhost", 8080, glm::mat4(1.0)},
                    Server{"gggggwergweg", 8080, glm::mat4(1.0)},
                    Server{"ki345234534", 8080, glm::mat4(1.0)},
                    Server{"pooyutjht", 8080, glm::mat4(1.0)}
            };

    PODS_SERIALIZABLE(
            5,
            PODS_MDR(servers))


};


int main() {

    /*
    ServerList original;

    pods::ResizableOutputBuffer out;
    pods::BinarySerializer<decltype(out)> serializer(out);
    if (serializer.save(original) != pods::Error::NoError)
    {
        std::cerr << "serialization error\n";
        return 1;
    }

    std::ofstream outFile;
    outFile.open("pods.dat", std::ios::out | std::ios::binary);


    if (outFile.is_open())
    {
        outFile.write(out.data(), out.size());
    }

    outFile.close();

    return 0;
    */
    if (hpms::MountFS("data/GAME.hpak")) {

        size_t size;
        ServerList* sl = hpms::LoadBinResource<ServerList>("pods.dat", &size);
        std::cout << "Server loaded successfully." << std::endl;
        for (Server s : sl->servers) {
            std::cout << s.port << " " << s.address << std::endl << PrintMatrix(s.m) << std::endl;
        }

        hpms::DeleteBinResource(sl);

    } else {
        std::cout << "Error, no HPAK found";
    }


}

std::string PrintMatrix(glm::mat4& m) {
    std::stringstream ss;
    ss << "[" << m[0][0] << "]" << "[" << m[0][1] << "]" << "[" << m[0][2] << "]" << "[" << m[0][3] << "]" << std::endl;
    ss << "[" << m[1][0] << "]" << "[" << m[1][1] << "]" << "[" << m[1][2] << "]" << "[" << m[1][3] << "]" << std::endl;
    ss << "[" << m[2][0] << "]" << "[" << m[2][1] << "]" << "[" << m[2][2] << "]" << "[" << m[2][3] << "]" << std::endl;
    ss << "[" << m[3][0] << "]" << "[" << m[3][1] << "]" << "[" << m[3][2] << "]" << "[" << m[3][3] << "]" << std::endl;
    return ss.str();
}