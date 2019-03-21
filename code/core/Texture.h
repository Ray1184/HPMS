/**
 * File Texture.h
 */
#pragma once

#include <string>
#include <stb_image.h>
#include "../common/FileSystem.h"

namespace hpms
{
    class Texture : public HPMSObject
    {
    private:
        int width;
        int height;
        int numComp;
        unsigned char* data;
        std::string path;
        bool loaded;
        bool clear;

    public:
        Texture(unsigned char* pdata, int pwidth, int pheight, int pnumComp, const std::string& name) :
                data(pdata),
                width(pwidth),
                height(pheight),
                numComp(pnumComp),
                path(name),
                clear(false)
        {

        }

        ~Texture()
        {
            FreeImageData();
        }


        inline void FreeImageData()
        {
            if (!clear)
            {
                clear = true;
                stbi_image_free(data);
            }
        }

        inline int GetWidth() const
        {
            return width;
        }

        inline int GetHeight() const
        {
            return height;
        }

        inline unsigned char* GetData() const
        {
            return data;
        }

        inline const std::string& GetPath() const
        {
            return path;
        }

        inline const std::string Name() const override
        {
            return "Texture";
        }
    };
}