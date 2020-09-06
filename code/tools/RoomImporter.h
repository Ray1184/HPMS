/*!
 * File RoomImporter.h
 */

#pragma once

#include <pugixml.hpp>
#include <utility>
#include "../logic/RoomModelItem.h"
#include "../common/Utils.h"

namespace hpms
{
    class RoomImporter
    {
    public:
        static hpms::RoomModelItem* LoadRoom(std::string& path);

    private:


        static void ProcessSectors(std::vector<hpms::Sector>& sectors, std::string& path);

        static void ProcessPerimetralSides(std::vector<hpms::Sector>& vector);


    };

    class Face
    {
    public:
        unsigned int indexA;

        unsigned int indexB;

        unsigned int indexC;

        std::string lineRef;

        Face(std::string  lineRef, const std::string& tokenX, const std::string& tokenY,
             const std::string& tokenZ) :
                lineRef(std::move(lineRef)),
                indexA(ProcessIndex(tokenX) - 1),
                indexB(ProcessIndex(tokenY) - 1),
                indexC(ProcessIndex(tokenZ) - 1)
        {

        }

    private:
        static inline unsigned int ProcessIndex(const std::string& token)
        {
            int sIndex = token.find('/');
            if (sIndex < 0)
            {
                return std::stoi(token);
            } else
            {
                return std::stoi(token.substr(0, sIndex));
            }
        }
    };

}

