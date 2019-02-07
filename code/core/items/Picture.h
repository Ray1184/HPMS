/*!
 * File LayerPicture.h
 */

#pragma once

#include "../RenderObject.h"
#include "../AdvModelItem.h"
#include "../Names.h"

namespace hpms
{

    enum PictureMode
    {
        FOREGROUND,
        BACKGROUND,
        DEPTH_MASK
    };

    class Picture : public RenderObject
    {
    private:
        std::string imagePath;
        float alpha;
        bool visible;
        float x;
        float y;
        PictureMode mode;
    public:

        explicit Picture(const std::string& pimagePath, PictureMode pmode = FOREGROUND) : alpha(1.0f),
                                                                                          visible(true),
                                                                                          imagePath(pimagePath),
                                                                                          x(0),
                                                                                          y(0),
                                                                                          mode(pmode)
        {

        }


        inline float GetAlpha() const
        {
            return alpha;
        }

        inline void SetAlpha(float alpha)
        {
            Picture::alpha = alpha;
        }

        inline bool IsVisible() const override
        {
            return visible;
        }

        inline void SetVisible(bool visible)
        {
            Picture::visible = visible;
        }

        inline float GetX() const
        {
            return x;
        }

        inline void SetX(float x)
        {
            Picture::x = x;
        }

        inline float GetY() const
        {
            return y;
        }

        inline void SetY(float y)
        {
            Picture::y = y;
        }

        inline const std::string& GetImagePath() const
        {
            return imagePath;
        }

        inline void SetImagePath(const std::string& imagePath)
        {
            Picture::imagePath = imagePath;
        }

        bool operator==(const Picture& rhs) const
        {
            return imagePath.compare(rhs.GetImagePath()) == 0;
        }

        bool operator!=(const Picture& rhs) const
        {
            return !(rhs == *this);
        }

        inline unsigned int GetTypeId() const override
        {
            return OBJ_TYPE_PICTURE;
        }

        inline PictureMode GetMode() const
        {
            return mode;
        }

        inline void SetMode(PictureMode mode)
        {
            Picture::mode = mode;
        }

    };
}
