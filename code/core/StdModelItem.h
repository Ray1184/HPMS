/*!
 * File StdModelItem.h
 */

#pragma once

#include <vector>
#include <string>
#include "Mesh.h"
#include <pods/pods.h>
#include <pods/buffers.h>
#include <pods/binary.h>
#include "../common/Utils.h"
#include "../common/HPMSObject.h"


namespace hpms
{
    class StdModelItem : public HPMSObject
    {
    protected:
        std::vector<Mesh> meshes;


    public:

        PODS_SERIALIZABLE(
                1,
                PODS_OPT(meshes)
        )


        const std::vector<Mesh>& GetMeshes() const
        {
            return meshes;
        }

        void SetMeshes(const std::vector<Mesh>& meshes)
        {
            StdModelItem::meshes = meshes;
        }

        virtual const std::string Name() const override
        {
            return "StdModelItem";
        }




    };


}
