/*!
 * File RoomImporter.h
 */

#include "RoomImporter.h"
#include "../logic/CalcUtils.h"
#include <map>

hpms::RoomModelItem* hpms::RoomImporter::LoadRoom(std::string& path)
{
    std::vector<hpms::Sector> sectors;
    ProcessSectors(sectors, path);
    std::string roomName = hpms::GetFileName(path);
    auto* map = hpms::SafeNew<RoomModelItem>(roomName, sectors);
    return map;
}

void hpms::RoomImporter::ProcessSectors(std::vector<hpms::Sector>& sectors, std::string& path)
{
    std::vector<glm::vec3> vertices;
    std::vector<hpms::Face> faces;
    std::unordered_map<std::string, std::string> faceRefToSectorName;
    std::unordered_map<std::string, hpms::Sector> sectorsById;
    std::string currentSector;


    auto process = [&vertices, &faces, &faceRefToSectorName, &currentSector, &sectorsById](const std::string& line)
    {
        std::vector<std::string> tokens = hpms::Split(line, "\\s+");
        char type = tokens[0].at(0);
        switch (type)
        {
            case 'o':
                currentSector = tokens[1];
                sectorsById.insert({tokens[1], hpms::Sector(tokens[1])});
                break;
            case 'v':
                vertices.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
                break;
            case 'f':
                faces.emplace_back(line, tokens[1], tokens[2], tokens[3]);
                faceRefToSectorName.insert({line, currentSector});
                break;
            default:
                break;
        }
    };
    hpms::ProcessFileLines(path, process);

    for (const auto& face : faces)
    {
        glm::vec3 t1 = glm::vec3(vertices[face.indexA].x, vertices[face.indexA].y, vertices[face.indexA].z);
        glm::vec3 t2 = glm::vec3(vertices[face.indexB].x, vertices[face.indexB].y, vertices[face.indexB].z);
        glm::vec3 t3 = glm::vec3(vertices[face.indexC].x, vertices[face.indexC].y, vertices[face.indexC].z);
        std::string sectorId = faceRefToSectorName[face.lineRef];
        Triangle tri = hpms::Triangle(sectorId, t1.x, t1.y, t1.z, t2.x, t2.y, t2.z, t3.x, t3.y, t3.z);
        sectorsById[sectorId].AddTriangle(tri);
    }

    for (const auto& sec : sectorsById)
    {
        hpms::Sector sector = sec.second;
        sectors.push_back(sector);
    }

    ProcessPerimetralSides(sectors);
}


void hpms::RoomImporter::ProcessPerimetralSides(std::vector<hpms::Sector>& sectors)
{
    std::vector<Triangle> allTris;
    for (auto& sector : sectors)
    {
        for (const auto& tri : sector.GetTriangles())
        {
            allTris.push_back(tri);
        }
    }


    for (auto& sector : sectors)
    {
        std::vector<Triangle> tris;
        for (Triangle tri : sector.GetTriangles())
        {
            tri.SetPerimetralSides(hpms::CalculatePerimetralSides(tri, allTris));
            tris.push_back(tri);
        }

        sector.SetTriangles(tris);
    }

}
