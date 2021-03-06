/*!
 * File ResourceItemsCache.cpp
 */

#include "ResourceItemsCache.h"

hpms::Texture* hpms::ResourceItemsCache::GetTexture(const std::string& name)
{
    if (textCache.find(name) == textCache.end())
    {
        int width;
        int height;
        int numComp;
#ifndef DATA_ARCHIVE
        unsigned char* data = stbi_load(name.c_str(), &width, &height, &numComp, STBI_rgb_alpha);
        if (!data)
        {
            std::stringstream ss;
            ss << "Impossible to open file " << name;
            LOG_ERROR(ss.str().c_str());
        }
#else
        hpms::FileSystem::MountFS(DATA_ARCHIVE);
                size_t size;
                void* buf = hpms::FileSystem::LoadRawResource(name, &size);
                unsigned char* data = stbi_load_from_memory((const stbi_uc*) buf, size, &width, &height, &numComp, STBI_rgb_alpha);
                hpms::SafeDeleteArray(buf);
#endif
        Texture* tex = hpms::SafeNew<Texture>(data, width, height, numComp, name);
        textCache[name] = tex;
    }

    return textCache[name];
}

hpms::AdvModelItem* hpms::ResourceItemsCache::GetModel(const std::string& name)
{

    if (modelsCache.find(name) == modelsCache.end())
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

            hpms::AdvModelItem* model = hpms::SafeNew<AdvModelItem>();
            pods::InputBuffer in(buffer, size);
            pods::BinaryDeserializer<decltype(in)> deserializer(in);
            if (deserializer.load(*model) != pods::Error::NoError)
            {
                std::stringstream ss;
                ss << "Impossible to deserialize model stored in " << name;
                LOG_ERROR(ss.str().c_str());
            }

            modelsCache[name] = model;
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
                hpms::AdvModelItem* model = hpms::FileSystem::LoadBinResource<AdvModelItem>(name, &size);
                modelsCache[name] = model;
#endif
    }

    return modelsCache[name];
}
