/*!
 * File RoomImporter.h
 */

#pragma once

#include <pugixml.hpp>
#include "../logic/Room.h"
#include "../common/Utils.h"

namespace hpms
{
    class RoomImporter
    {
    public:
        static hpms::Room* LoadRoom(std::string& path);

    private:

        static void ProcessSectorGroups(std::vector<hpms::SectorGroup>& sectorGroups, pugi::xml_node& parent);

        static void ProcessSectors(std::vector<hpms::Sector>& sectors, pugi::xml_node& parent);

        static void ProcessPerimetralSides(std::vector<hpms::Side>& sides, pugi::xml_node& parent);

        static void ProcessTriggers(std::vector<hpms::Trigger>& triggers, pugi::xml_node& parent);

        static void ProcessCalls(std::vector<hpms::Call>& calls, pugi::xml_node& parent);

        static void ProcessCallParameters(std::vector<hpms::Param>& params, pugi::xml_node& parent);

    };

}

