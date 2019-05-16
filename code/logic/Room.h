/*!
 * File Room.h
 */

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <pods/pods.h>
#include "../common/HPMSObject.h"

namespace hpms
{


    class Side
    {

    public:

        unsigned int idx1, idx2;

        Side(unsigned int idx1, unsigned int idx2) : idx1(idx1), idx2(idx2)
        {}

        Side()
        {}

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(idx1),
                PODS_OPT(idx2)

        );


        bool operator==(const Side& rhs) const
        {
            return idx1 == rhs.idx1 && idx2 == rhs.idx2;
        }

        bool operator!=(const Side& rhs) const
        {
            return !(rhs == *this);
        }
    };

    class Sector
    {
    private:

        std::string id;
        std::string groupId;

        std::vector<Side> perimetralSides;


    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(id),
                PODS_OPT(groupId),
                PODS_OPT(perimetralSides),
                PODS_OPT(x1),
                PODS_OPT(y1),
                PODS_OPT(z1),
                PODS_OPT(x2),
                PODS_OPT(y2),
                PODS_OPT(z2),
                PODS_OPT(x3),
                PODS_OPT(y3),
                PODS_OPT(z3)

        );

        float x1, y1, z1;
        float x2, y2, z2;
        float x3, y3, z3;

        Sector(const std::string& id, const std::string& groupId,
               const std::vector<Side>& perimetralSides, float x1, float y1, float z1, float x2, float y2, float z2,
               float x3, float y3, float z3) : id(id), groupId(groupId),
                                               perimetralSides(perimetralSides), x1(x1), y1(y1), z1(z1), x2(x2), y2(y2),
                                               z2(z2), x3(x3), y3(y3), z3(z3)
        {}

        Sector(const std::string& id, const std::string& groupId,
               const std::vector<Side>& perimetralSides) : id(id), groupId(groupId),
                                                           perimetralSides(perimetralSides)
        {}

        Sector()
        {}

        bool IsPerimetral() const
        {
            return !perimetralSides.empty();
        }

        const std::string& GetId() const
        {
            return id;
        }

        void SetId(const std::string& id)
        {
            Sector::id = id;
        }

        const std::string& GetGroupId() const
        {
            return groupId;
        }

        void SetGroupId(const std::string& groupId)
        {
            Sector::groupId = groupId;
        }

        const std::vector<Side>& GetPerimetralSides() const
        {
            return perimetralSides;
        }

        void SetPerimetralSides(const std::vector<Side>& perimetralSides)
        {
            Sector::perimetralSides = perimetralSides;
        }

        bool operator==(const Sector& rhs) const
        {
            return id == rhs.id;
        }

        bool operator!=(const Sector& rhs) const
        {
            return !(rhs == *this);
        }

    };

    class Param
    {
    public:
        int type; // 0 - string, 1 - int, 2 - float
        std::string sVal;
        int iVal;
        float fVal;

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(type),
                PODS_OPT(sVal),
                PODS_OPT(iVal),
                PODS_OPT(fVal)
        );


    };


    class Call
    {
    private:
        std::string functionName;
        std::vector<Param> parameters;

    public:
        Call(const std::string& functionName) : functionName(functionName)
        {}

        Call(const std::string& functionName, const std::vector<Param>& parameters) : functionName(functionName),
                                                                                      parameters(parameters)
        {}

        Call()
        {}

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(functionName),
                PODS_OPT(parameters)
        );

        const std::string& GetFunctionName() const
        {
            return functionName;
        }

        void SetFunctionName(const std::string& functionName)
        {
            Call::functionName = functionName;
        }

        const std::vector<Param>& GetParameters() const
        {
            return parameters;
        }

        void SetParameters(const std::vector<Param>& parameters)
        {
            Call::parameters = parameters;
        }
    };


    class Trigger
    {

    private:

        std::vector<Call> conditions;
        std::vector<Call> actions;

    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(conditions),
                PODS_OPT(actions)
        );

        Trigger(const std::vector<Call>& conditions,
                const std::vector<Call>& actions) : conditions(conditions),
                                                    actions(actions)
        {}


        Trigger()
        {}


        const std::vector<Call>& GetConditions() const
        {
            return conditions;
        }

        void SetConditions(const std::vector<Call>& conditions)
        {
            Trigger::conditions = conditions;
        }

        const std::vector<Call>& GetActions() const
        {
            return actions;
        }

        void SetActions(const std::vector<Call>& actions)
        {
            Trigger::actions = actions;
        }

    };


    class SectorGroup
    {
    private:
        std::string id;
        std::vector<Sector> sectors;


    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(id),
                PODS_OPT(sectors)

        );

        SectorGroup(const std::string& id, const std::vector<Sector>& sectors, const std::vector<Trigger>& triggers)
                : id(id), sectors(sectors)
        {}

        SectorGroup()
        {}

        const std::string& GetId() const
        {
            return id;
        }

        void SetId(const std::string& id)
        {
            SectorGroup::id = id;
        }


        const std::vector<Sector>& GetSectors() const
        {
            return sectors;
        }

        void SetSectors(const std::vector<Sector>& sectors)
        {
            SectorGroup::sectors = sectors;
        }

        bool operator==(const SectorGroup& rhs) const
        {
            return id == rhs.id;
        }

        bool operator!=(const SectorGroup& rhs) const
        {
            return !(rhs == *this);
        }
    };

    class Room : public hpms::HPMSObject
    {
    private:
        std::vector<SectorGroup> sectorGroups;
        std::vector<Trigger> triggers;
        std::string id;

    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(id),
                PODS_OPT(sectorGroups),
                PODS_OPT(triggers)

        );

        Room(const std::vector<SectorGroup>& sectorGroups, const std::vector<Trigger>& triggers) : sectorGroups(
                sectorGroups), triggers(triggers)
        {}

        Room(const std::vector<Trigger>& triggers) : triggers(triggers)
        {}

        Room(const std::vector<SectorGroup>& sectorGroups) : sectorGroups(sectorGroups)
        {}

        Room()
        {}

        const std::vector<SectorGroup>& GetSectorGroups() const
        {
            return sectorGroups;
        }

        void SetSectorGroups(const std::vector<SectorGroup>& sectorGroups)
        {
            Room::sectorGroups = sectorGroups;
        }

        const std::vector<Trigger>& GetTriggers() const
        {
            return triggers;
        }

        void SetTriggers(const std::vector<Trigger>& triggers)
        {
            Room::triggers = triggers;
        }

        const std::string& GetId() const
        {
            return id;
        }

        void SetId(const std::string& id)
        {
            Room::id = id;
        }

        virtual const std::string Name() const override
        {
            return "Room";
        }

    };


}
