/*!
 * File RoomToHDATConverterMain.h
 */

#include <string>
#include <iostream>
#include <pods/json.h>
#include <pods/buffers.h>
#include <fstream>
#include "../logic/RoomModelItem.h"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Arguments number " << argc - 1 << ", expected 2" << std::endl;
        return -1;
    }

    std::string outPath(argv[1]);
    std::string roomPath(argv[2]);

    // TEST JSON
    pods::ResizableOutputBuffer out;
    pods::PrettyJsonSerializer<decltype(out)> serializer(out);


    // Populate
    hpms::Side d1(0, 1);
    hpms::Side d2(1, 2);

    std::vector<hpms::Side> sides;
    sides.push_back(d1);
    sides.push_back(d2);

    hpms::Sector s1("S1", "G1", sides, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0);
    hpms::Sector s2("S2", "G1", std::vector<hpms::Side>(), 0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0);
    hpms::Sector s3("S3", "G1", std::vector<hpms::Side>(), 0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0);

    std::vector<hpms::Sector> sectors;
    sectors.push_back(s1);
    sectors.push_back(s2);
    sectors.push_back(s3);

    hpms::Param playerId;
    playerId.type = 0;
    playerId.sVal = "PLAYER";

    hpms::Param hpId;
    hpId.type = 0;
    hpId.sVal = "HP";

    hpms::Param hpVal;
    hpVal.type = 1;
    hpVal.iVal = -1;

    std::vector<hpms::Param> params;
    params.push_back(playerId);
    params.push_back(hpId);
    params.push_back(hpVal);

    hpms::Action action("incr_decr_entity_param", params, 1, 1000);

    hpms::Condition cond("test_condition");

    std::vector<hpms::Action> actions;
    actions.push_back(action);

    std::vector<hpms::Condition> conditions;
    conditions.push_back(cond);

    hpms::Trigger trigger("PLAYER", conditions, actions);

    std::vector<hpms::Trigger> triggers;
    triggers.push_back(trigger);



    hpms::SectorGroup sg("G1", sectors, triggers);
    std::vector<hpms::SectorGroup> groups;
    groups.push_back(sg);
    hpms::Floor* floor = new hpms::Floor(groups);



    if (serializer.save(*floor) != pods::Error::NoError)
    {
        std::cerr << "Error serializing test JSON" << std::endl;
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
    // END TEST

    return 0;
}
