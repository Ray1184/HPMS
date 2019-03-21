/**
 * File LuaRegister.h
 */
#pragma once

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "LuaExtensions.h"
#include "../../core/items/Entity.h"
#include "../input/KeyEvent.h"

using namespace luabridge;

namespace hpms
{
    class LuaRegister
    {
    public:

        static void RegisterAssetManager(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .addFunction("make_entity", &hpms::AMCreateEntity)
                    .addFunction("delete_entity", &hpms::AMDeleteEntity)
                    .addFunction("make_background", &hpms::AMCreateBackground)
                    .addFunction("delete_background", &hpms::AMDeleteBackground)
                    .addFunction("make_picture", &hpms::AMCreateForeground)
                    .addFunction("delete_picture", &hpms::AMDeleteForeground)
                    .addFunction("make_depth_mask", &hpms::AMCreateDepthMask)
                    .addFunction("delete_depth_mask", &hpms::AMDeleteDepthMask)
                    .addFunction("add_entity_to_scene", &hpms::AMAddEntityToScene)
                    .addFunction("add_picture_to_scene", &hpms::AMAddPictureToScene)
                    .endNamespace();
        }

        static void RegisterEntity(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<hpms::Entity>("entity")
                    .addProperty("position", &hpms::Entity::GetPosition, &hpms::Entity::SetPosition)
                    .addProperty("scale", &hpms::Entity::GetScale, &hpms::Entity::SetScale)
                    .addProperty("rotation", &hpms::Entity::GetRotation, &hpms::Entity::SetRotation)
                    .addProperty("anim_index", &hpms::Entity::GetAnimCurrentIndex, &hpms::Entity::SetAnimCurrentIndex)
                    .addProperty("anim_frame_index", &hpms::Entity::GetAnimCurrentFrameIndex,
                                 &hpms::Entity::SetAnimCurrentFrameIndex)
                    .addProperty("visible", &hpms::Entity::IsVisible, &hpms::Entity::SetVisible)
                    .addProperty("anim_loop", &hpms::Entity::IsAnimLoop, &hpms::Entity::SetAnimLoop)
                    .addProperty("anim_play", &hpms::Entity::IsAnimPlay, &hpms::Entity::SetAnimPlay)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterPicture(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<hpms::Picture>("picture")
                    .addProperty("alpha", &hpms::Picture::GetAlpha, &hpms::Picture::SetAlpha)
                    .addProperty("x", &hpms::Picture::GetX, &hpms::Picture::SetX)
                    .addProperty("y", &hpms::Picture::GetY, &hpms::Picture::SetY)
                    .addProperty("visible", &hpms::Picture::IsVisible, &hpms::Picture::SetVisible)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterCommonMath(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .addFunction("to_radians", &hpms::ToRadians)
                    .addFunction("to_degrees", &hpms::ToDegrees)
                    .endNamespace();

        }

        static void RegisterQuaternion(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::quat>("quat")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float, float, float) > ()
                    .addData("x", &glm::quat::x)
                    .addData("y", &glm::quat::y)
                    .addData("z", &glm::quat::z)
                    .addData("w", &glm::quat::w)
                    .endClass()
                    .addFunction("quat_mul", &hpms::MulQuat)
                    .addFunction("from_axis", &hpms::FromAxisQuat)
                    .endNamespace();

        }

        static void RegisterVector3(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec3>("vec3")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float, float) > ()
                    .addData("x", &glm::vec3::x)
                    .addData("y", &glm::vec3::y)
                    .addData("z", &glm::vec3::z)
                    .endClass()
                    .addFunction("vec3_add", &hpms::SumVec3)
                    .addFunction("vec3_sub", &hpms::SubVec3)
                    .addFunction("vec3_mul", &hpms::MulVec3)
                    .addFunction("vec3_div", &hpms::DivVec3)
                    .addFunction("vec3_dist", &hpms::DistVec3)
                    .addFunction("vec3_dot", &hpms::DotVec3)
                    .addFunction("vec3_cross", &hpms::CrossVec3)
                    .endNamespace();

        }

        static void RegisterVector4(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec4>("vec4")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float, float, float) > ()
                    .addData("w", &glm::vec4::w)
                    .addData("x", &glm::vec4::x)
                    .addData("y", &glm::vec4::y)
                    .addData("z", &glm::vec4::z)
                    .endClass()
                    .addFunction("vec4_add", &hpms::SumVec4)
                    .addFunction("vec4_sub", &hpms::SubVec4)
                    .addFunction("vec4_mul", &hpms::MulVec4)
                    .addFunction("vec4_div", &hpms::DivVec4)
                    .addFunction("vec4_dot", &hpms::DotVec4)
                    .endNamespace();

        }

        static void RegisterVector2(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec2>("vec2")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float) > ()
                    .addData("x", &glm::vec2::x)
                    .addData("y", &glm::vec2::y)
                    .endClass()
                    .addFunction("vec2_add", &hpms::SumVec2)
                    .addFunction("vec2_sub", &hpms::SubVec2)
                    .addFunction("vec2_mul", &hpms::MulVec2)
                    .addFunction("vec2_div", &hpms::DivVec2)
                    .addFunction("vec2_dist", &hpms::DistVec2)
                    .addFunction("vec2_dot", &hpms::DotVec2)
                    .endNamespace();

        }

        static void RegisterMatrix4(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::mat4>("mat4")
                    .addConstructor < void(*)
            (void) > ()
                    .endClass()
                    .addFunction("mat4_add", &hpms::SumMat4)
                    .addFunction("mat4_sub", &hpms::SubMat4)
                    .addFunction("mat4_mul", &hpms::MulMat4)
                    .addFunction("mat4_div", &hpms::DivMat4)
                    .addFunction("mat4_elem_at", &hpms::ElemAtMat4)
                    .endNamespace();

        }

        static void RegisterKeyEvent(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<KeyEvent>("key_event")
                    .addData("key", &KeyEvent::key)
                    .addData("input_type", &KeyEvent::inputType)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterScene(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Scene>("scene")
                    .addProperty("ambient_light", &hpms::Scene::GetAmbientLight, &hpms::Scene::SetAmbientLight)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterCamera(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Camera>("camera")
                    .addProperty("position", &hpms::Camera::GetPosition, &hpms::Camera::SetPosition)
                    .addProperty("rotation", &hpms::Camera::GetRotation, &hpms::Camera::SetRotation)
                    .endClass()
                    .endNamespace();
        }
    };
}
