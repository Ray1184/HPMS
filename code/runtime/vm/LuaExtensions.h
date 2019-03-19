/**
 * File LuaExtensions.h
 */

#pragma once

#include <glm/glm.hpp>
#include <math.h>

#include "../../core/items/Entity.h"
#include "../../core/ResourceCache.h"
#include "../../core/Camera.h"
#include "../../core/Scene.h"

namespace hpms
{

    // LUA Math.
    glm::quat MulQuat(const glm::quat& q1, const glm::quat& q2)
    {
        return q1 * q2;
    }

    glm::quat FromAxisQuat(float angle, float xAxis, float yAxis, float zAxis)
    {
        return glm::angleAxis(angle, glm::vec3(xAxis, yAxis, zAxis));
    }

    float ToRadians(float degrees)
    {
        return glm::radians(degrees);
    }

    float ToDegrees(float radians)
    {
        return glm::degrees(radians);
    }

    glm::vec3 SumVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return v1 + v2;
    }

    glm::vec3 SubVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return v1 - v2;
    }

    glm::vec3 MulVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return v1 * v2;
    }

    glm::vec3 DivVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return v1 / v2;
    }


    glm::vec3 NormVec3(const glm::vec3& v)
    {
        return glm::normalize(v);
    }

    float DistVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
    }

    float DotVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return glm::dot(v1, v2);
    }

    glm::vec3 CrossVec3(const glm::vec3& v1, const glm::vec3& v2)
    {
        return glm::cross(v1, v2);
    }

    glm::vec4 SumVec4(const glm::vec4& v1, const glm::vec4& v2)
    {
        return v1 + v2;
    }

    glm::vec4 SubVec4(const glm::vec4& v1, const glm::vec4& v2)
    {
        return v1 - v2;
    }

    glm::vec4 MulVec4(const glm::vec4& v1, const glm::vec4& v2)
    {
        return v1 * v2;
    }

    glm::vec4 DivVec4(const glm::vec4& v1, const glm::vec4& v2)
    {
        return v1 / v2;
    }

    glm::vec4 NormVec4(const glm::vec4& v)
    {
        return glm::normalize(v);
    }

    float DotVec4(const glm::vec4& v1, const glm::vec4& v2)
    {
        return glm::dot(v1, v2);
    }

    glm::vec2 SumVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return v1 + v2;
    }

    glm::vec2 SubVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return v1 - v2;
    }

    glm::vec2 MulVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return v1 * v2;
    }

    glm::vec2 DivVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return v1 / v2;
    }


    glm::vec2 NormVec2(const glm::vec2& v)
    {
        return glm::normalize(v);
    }

    float DistVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
    }

    float DotVec2(const glm::vec2& v1, const glm::vec2& v2)
    {
        return glm::dot(v1, v2);
    }


    glm::mat4 SumMat4(const glm::mat4& v1, const glm::mat4& v2)
    {
        return v1 + v2;
    }

    glm::mat4 SubMat4(const glm::mat4& v1, const glm::mat4& v2)
    {
        return v1 - v2;
    }

    glm::mat4 MulMat4(const glm::mat4& v1, const glm::mat4& v2)
    {
        return v1 * v2;
    }

    glm::mat4 DivMat4(const glm::mat4& v1, const glm::mat4& v2)
    {
        return v1 / v2;
    }

    float ElemAtMat4(const glm::mat4& v, int i, int j)
    {
        return v[i][j];
    }

    // STL utils.


    // LUA Asset Manager.
    hpms::Entity* AMCreateEntity(const std::string& name)
    {
        AdvModelItem* testModel = ResourceCache::Instance().GetModel(name);
        hpms::Entity* e = hpms::SafeNew<hpms::Entity>(testModel);
        return e;
    }

    void AMDeleteEntity(Entity* entity)
    {
        hpms::SafeDelete(entity);
    }


    hpms::Picture* AMCreateBackground(const std::string& path)
    {
        hpms::Picture* p = hpms::SafeNew<hpms::Picture>(path, PictureMode::BACKGROUND);
        return p;
    }

    void AMDeleteBackground(Picture* pic)
    {
        hpms::SafeDelete(pic);
    }

    hpms::Picture* AMCreateForeground(const std::string& path)
    {
        hpms::Picture* p = hpms::SafeNew<hpms::Picture>(path, PictureMode::FOREGROUND);
        return p;
    }

    void AMDeleteForeground(Picture* pic)
    {
        hpms::SafeDelete(pic);
    }

    hpms::Picture* AMCreateDepthMask(const std::string& path)
    {
        hpms::Picture* p = hpms::SafeNew<hpms::Picture>(path, PictureMode::DEPTH_MASK);
        return p;
    }

    void AMDeleteDepthMask(Picture* pic)
    {
        hpms::SafeDelete(pic);
    }

    void AMAddObjToScene(RenderObject* obj, Scene* scene)
    {
        scene->AddRenderObject(obj);
    }

}
