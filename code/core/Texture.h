/**
 * File Texture.h
 */
#pragma once

#include <string>
#include <stb_image.h>
#include "../common/FileSystem.h"

namespace hpms
{
    class Texture
    {
    private:
        int width;
        int height;
        int numComp;
        unsigned char* data;
        std::string path;
        bool loaded;

    public:
        Texture(unsigned char* pdata, int pwidth, int pheight, int pnumComp, const std::string& name) :
                data(pdata),
                width(pwidth),
                height(pheight),
                numComp(pnumComp),
                path(name)
        {

        }

        ~Texture()
        {
            FreeImageData();
        }


        inline void FreeImageData()
        {
            stbi_image_free(data);
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
    };
}