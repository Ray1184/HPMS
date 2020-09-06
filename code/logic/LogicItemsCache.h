/*!
 * File LogicItemsCache.h
 */

#pragma once

#include <unordered_map>
#include <pods/buffers.h>
#include <pods/binary.h>
#include "../common/HPMSObject.h"
#include "RoomModelItem.h"
#include "../common/Utils.h"

namespace hpms
{
    class LogicItemsCache : public hpms::HPMSObject
    {
    private:
        LogicItemsCache()
        {};

        LogicItemsCache(const LogicItemsCache&);

        LogicItemsCache& operator=(const LogicItemsCache&);

        std::unordered_map<std::string, RoomModelItem*> mapCache;

        inline void FreeRoomMaps()
        {
            for (auto entry : mapCache)
            {
                hpms::SafeDelete(entry.second);
            }
            mapCache.clear();
        }

    public:
        inline static LogicItemsCache& Instance()
        {
            static LogicItemsCache inst;
            return inst;
        }

        RoomModelItem* GetRoomMap(const std::string& name);



        inline void FreeAll()
        {
            FreeRoomMaps();
        }

        inline const std::string Name() const override
        {
            return "LogicItemsCache";
        }
    };


}