/*!
 * File Animation.h
 */

#pragma once

#include <vector>
#include <glm/mat4x4.hpp>
#include <string>
#include <pods/pods.h>

#define MAX_JOINTS 150

namespace hpms
{
    struct FrameTransform
    {
        glm::mat4 jointMatrix;

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(jointMatrix[0][0]),
                PODS_OPT(jointMatrix[0][1]),
                PODS_OPT(jointMatrix[0][2]),
                PODS_OPT(jointMatrix[0][3]),
                PODS_OPT(jointMatrix[1][0]),
                PODS_OPT(jointMatrix[1][1]),
                PODS_OPT(jointMatrix[1][2]),
                PODS_OPT(jointMatrix[1][3]),
                PODS_OPT(jointMatrix[2][0]),
                PODS_OPT(jointMatrix[2][1]),
                PODS_OPT(jointMatrix[2][2]),
                PODS_OPT(jointMatrix[2][3]),
                PODS_OPT(jointMatrix[3][0]),
                PODS_OPT(jointMatrix[3][1]),
                PODS_OPT(jointMatrix[3][2]),
                PODS_OPT(jointMatrix[3][3])
        )

    };

    struct Frame
    {

        std::vector<FrameTransform> frameTransformations;

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(frameTransformations)
        )

    };


    class Animation
    {

    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(frames),
                PODS_OPT(name),
                PODS_OPT(duration)
        );


        Animation() :
                name(std::string()),
                frames(0),
                duration(0)
        {}

        Animation(std::string pname, std::vector<Frame>& pframes, double pduration) :
                name(pname),
                frames(pframes),
                duration(pduration)
        {}

        inline const std::vector<Frame>& GetFrames() const
        {
            return frames;
        }

        inline void SetFrames(const std::vector<Frame>& frames)
        {
            Animation::frames = frames;
        }

        inline const std::string& GetName() const
        {
            return name;
        }

        inline void SetName(const std::string& name)
        {
            Animation::name = name;
        }

        inline double GetDuration() const
        {
            return duration;
        }

        inline void SetDuration(double duration)
        {
            Animation::duration = duration;
        }



    private:
        std::vector<Frame> frames;
        std::string name;
        double duration;

    };
}


