/*!
 * File WalkMap.h
 */

#pragma once

#include <utility>

#include "../../common/HPMSObject.h"
#include "../RoomModelItem.h"

namespace hpms
{
    class WalkMap : public HPMSObject
    {
    private:
        std::string name;
        hpms::RoomModelItem* roomModelItem;
    public:

        explicit WalkMap(const std::string& name) : name(name), roomModelItem(nullptr)
        {}

        WalkMap(const std::string& name, RoomModelItem* roomModelItem) : name(name), roomModelItem(roomModelItem)
        {}


        inline const std::string& GetName() const
        {
            return name;
        }

        inline void SetName(const std::string& name)
        {
            WalkMap::name = name;
        }

        inline RoomModelItem* GetRoomModelItem() const
        {
            return roomModelItem;
        }

        inline void SetRoomModelItem(RoomModelItem* roomModelItem)
        {
            WalkMap::roomModelItem = roomModelItem;
        }

        inline bool DummyMap() const
        {
            return roomModelItem == nullptr;
        }

        inline const std::string Name() const override
        {
            return "WalkMap";
        }
    };
}
