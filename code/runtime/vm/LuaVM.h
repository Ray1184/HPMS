/*!
 * File LuaVM.h
 */

#pragma once

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <string>


#include <glm/glm.hpp>
#include "LuaRegister.h"
#include "../../common/Utils.h"

namespace hpms
{
    class LuaVM : HPMSObject
    {

    public:
        LuaVM() : closed(false)
        {
            state = luaL_newstate();
            luaL_openlibs(state);
        }

        virtual ~LuaVM()
        {
            if (!closed)
            {
                Close();
            }
        }

        inline void ExecuteScript(const std::string& path)
        {

            luaL_dofile(state, path.c_str());
            lua_pcall(state, 0, 0, 0);

        }

        inline void ExecuteStatement(const std::string& stat)
        {

            luaL_dostring(state, stat.c_str());
            lua_pcall(state, 0, 0, 0);

        }

        inline LuaRef GetGlobal(const std::string& name)
        {
            return getGlobal(state, name.c_str());
        }


        inline void RegisterAll()
        {
            hpms::LuaRegister::RegisterCommonMath(state);
            hpms::LuaRegister::RegisterVector2(state);
            hpms::LuaRegister::RegisterVector3(state);
            hpms::LuaRegister::RegisterVector4(state);
            hpms::LuaRegister::RegisterMatrix4(state);
            hpms::LuaRegister::RegisterKeyEvent(state);
            hpms::LuaRegister::RegisterKeyList(state);
            hpms::LuaRegister::RegisterQuaternion(state);
            hpms::LuaRegister::RegisterEntity(state);
            hpms::LuaRegister::RegisterNode(state);
            hpms::LuaRegister::RegisterPicture(state);
            hpms::LuaRegister::RegisterAssetManager(state);
            hpms::LuaRegister::RegisterScene(state);
            hpms::LuaRegister::RegisterCamera(state);
        }

        inline void Close()
        {
            lua_close(state);
            closed = true;
        }

        inline const std::string Name() const override
        {
            return "LuaVM";
        }

    private:
        lua_State* state;
        bool closed;
    };
}
