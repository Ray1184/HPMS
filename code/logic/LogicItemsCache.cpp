/*!
 * File LogicItemsCache.cpp
 */

#include "LogicItemsCache.h"

hpms::RoomModelItem* hpms::LogicItemsCache::GetRoomMap(const std::string& name)
{
    if (mapCache.find(name) == mapCache.end())
    {
#ifndef DATA_ARCHIVE
        std::ifstream file(name, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            std::stringstream ss;
            ss << "Impossible to open file " << name;
            LOG_ERROR(ss.str().c_str());
        }
        size_t size = file.tellg();

        file.seekg(0, std::ios::beg);

        char* buffer = hpms::SafeNewArray<char>(size);


        if (file.read(buffer, size))
        {

            hpms::RoomModelItem* map = hpms::SafeNew<RoomModelItem>();
            pods::InputBuffer in(buffer, size);
            pods::BinaryDeserializer<decltype(in)> deserializer(in);
            if (deserializer.load(*map) != pods::Error::NoError)
            {
                std::stringstream ss;
                ss << "Impossible to deserialize room map stored in " << name;
                LOG_ERROR(ss.str().c_str());
            }

            mapCache[name] = map;
            hpms::SafeDeleteArray(buffer);
        } else
        {
            std::stringstream ss;
            ss << "Impossible to read file " << name;
            LOG_ERROR(ss.str().c_str());
        }
#else
        hpms::FileSystem::MountFS(DATA_ARCHIVE);
                size_t size;
                hpms::RoomMap* model = hpms::FileSystem::LoadBinResource<RoomMap>(name, &size);
                mapCache[name] = model;
#endif
    }

    return mapCache[name];
}
