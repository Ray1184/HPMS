/*!
 * File LayerPicture.h
 */

#pragma once

#include "RenderObject.h"
#include "AdvModelItem.h"

namespace hpms
{

    class LayerPicture : public RenderObject
    {
    private:
        std::string imagePath;
        float virtualDepth;
        float alpha;
        bool visible;
        float x;
        float y;
    public:

        LayerPicture(const std::string& pimagePath) : virtualDepth(0.0f),
                                                      alpha(1.0f),
                                                      visible(true),
                                                      imagePath(pimagePath),
                                                      x(0),
                                                      y(0)
        {

        }


        inline float GetVirtualDepth() const override
        {
            return virtualDepth;
        }

        inline void SetVirtualDepth(float virtualDepth)
        {
            LayerPicture::virtualDepth = virtualDepth;
        }

        inline float GetAlpha() const
        {
            return alpha;
        }

        inline void SetAlpha(float alpha)
        {
            LayerPicture::alpha = alpha;
        }

        inline bool IsVisible() const override
        {
            return visible;
        }

        inline void SetVisible(bool visible)
        {
            LayerPicture::visible = visible;
        }

        inline float GetX() const
        {
            return x;
        }

        inline void SetX(float x)
        {
            LayerPicture::x = x;
        }

        inline float GetY() const
        {
            return y;
        }

        inline void SetY(float y)
        {
            LayerPicture::y = y;
        }

        inline const std::string& GetImagePath() const
        {
            return imagePath;
        }

        inline void SetImagePath(const std::string& imagePath)
        {
            LayerPicture::imagePath = imagePath;
        }

    };
}
