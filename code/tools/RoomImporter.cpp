/*!
 * File RoomImporter.h
 */

#include "RoomImporter.h"


hpms::Room* hpms::RoomImporter::LoadRoom(std::string& path)
{
    hpms::Room* floor = hpms::SafeNew<Room>();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result)
    {
        std::stringstream ss;
        ss << "Error importing room from " << path << std::endl;
        LOG_ERROR(ss.str().c_str());
        hpms::SafeDelete(floor);
        return nullptr;
    }
    std::vector<SectorGroup> sectorGroups;
    std::vector<Trigger> triggers;
    pugi::xml_node rootNode = doc.child("room");
    floor->SetId(rootNode.attribute("id").value());
    pugi::xml_node grsNode = rootNode.child("sectorGroups");
    pugi::xml_node triggersNode = rootNode.child("triggers");
    ProcessSectorGroups(sectorGroups, grsNode);
    ProcessTriggers(triggers, triggersNode);
    floor->SetSectorGroups(sectorGroups);
    floor->SetTriggers(triggers);
    return floor;
}

void hpms::RoomImporter::ProcessSectorGroups(std::vector<hpms::SectorGroup>& sectorGroups, pugi::xml_node& parent)
{
    for (pugi::xml_node sgNode: parent.children("sectorGroup"))
    {
        SectorGroup sg;
        sg.SetId(sgNode.attribute("id").value());
        std::vector<Sector> sectors;
        pugi::xml_node scsNode = sgNode.child("sectors");
        ProcessSectors(sectors, scsNode);
        sg.SetSectors(sectors);
        sectorGroups.push_back(sg);
    }
}

void hpms::RoomImporter::ProcessSectors(std::vector<hpms::Sector>& sectors, pugi::xml_node& parent)
{
    for (pugi::xml_node secNode: parent.children("sector"))
    {
        Sector sec;
        sec.SetId(secNode.attribute("id").value());
        sec.SetGroupId(secNode.attribute("groupId").value());
        sec.x1 = secNode.attribute("x1").as_float();
        sec.x2 = secNode.attribute("x2").as_float();
        sec.x3 = secNode.attribute("x3").as_float();
        sec.y1 = secNode.attribute("y1").as_float();
        sec.y2 = secNode.attribute("y2").as_float();
        sec.y3 = secNode.attribute("y3").as_float();
        sec.z1 = secNode.attribute("z1").as_float();
        sec.z2 = secNode.attribute("z2").as_float();
        sec.z3 = secNode.attribute("z3").as_float();
        std::vector<hpms::Side> sides;
        pugi::xml_node sdsNode = secNode.child("perimetralSides");
        ProcessPerimetralSides(sides, sdsNode);
        sec.SetPerimetralSides(sides);
        sectors.push_back(sec);

    }
}

void hpms::RoomImporter::ProcessPerimetralSides(std::vector<hpms::Side>& sides, pugi::xml_node& parent)
{
    for (pugi::xml_node sdNode: parent.children("perimetralSide"))
    {
        Side side;
        side.idx1 = sdNode.attribute("idx1").as_uint();
        side.idx2 = sdNode.attribute("idx2").as_uint();
        sides.push_back(side);
    }
}

void hpms::RoomImporter::ProcessTriggers(std::vector<hpms::Trigger>& triggers, pugi::xml_node& parent)
{
    for (pugi::xml_node trNode: parent.children("trigger"))
    {
        Trigger trigger;
        pugi::xml_node condsNode = trNode.child("conditions");
        std::vector<hpms::Call> conditions;
        ProcessCalls(conditions, condsNode);
        trigger.SetConditions(conditions);
        pugi::xml_node actsNode = trNode.child("actions");
        std::vector<hpms::Call> actions;
        ProcessCalls(actions, actsNode);
        trigger.SetActions(actions);
        triggers.push_back(trigger);

    }
}

void hpms::RoomImporter::ProcessCalls(std::vector<hpms::Call>& calls, pugi::xml_node& parent)
{
    for (pugi::xml_node clNode: parent.children("call"))
    {
        Call call;
        call.SetFunctionName(clNode.attribute("functionName").value());
        pugi::xml_node paramsNode = clNode.child("params");
        std::vector<hpms::Param> params;
        ProcessCallParameters(params, paramsNode);
        call.SetParameters(params);
        calls.push_back(call);
    }
}

void hpms::RoomImporter::ProcessCallParameters(std::vector<hpms::Param>& params, pugi::xml_node& parent)
{
    for (pugi::xml_node paramNode: parent.children("param"))
    {
        Param param;
        param.type = paramNode.attribute("type").as_uint();
        switch (param.type)
        {
            case 1:
                param.iVal = paramNode.attribute("iVal").as_int();
                param.fVal = 0.0f;
                param.sVal = "";
                break;
            case 2:
                param.fVal = paramNode.attribute("fVal").as_float();
                param.iVal = 0;
                param.sVal = "";
                break;
            default:
                param.sVal = paramNode.attribute("sVal").value();
                param.fVal = 0.0f;
                param.iVal = 0;
                break;
        }
        params.push_back(param);
    }
}
