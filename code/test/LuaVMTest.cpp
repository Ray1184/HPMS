/*!
 * File LuaVMTest.h
 */



#include "../runtime/vm/LuaVM.h"
#include "../runtime/HPMSLogic.h"

int main()
{

    try
    {
        hpms::HPMSLogic* logic;
        auto* vm = new hpms::LuaVM();
        vm->RegisterAll();
        vm->ExecuteScript("data/scripts/Test.lua");
        LuaRef t = vm->GetGlobal("scene");
        LuaRef c = t["setup"];
        hpms::Entity* ret = c();
        auto item = ret->GetModelItem();
        size_t i = 1;
        for (const hpms::Mesh& m : item->GetMeshes())
        {
            std::cout << "Mesh " << i++ << std::endl;
            std::cout << "Key: " << m.GetKey() << std::endl;
        }

        vm->Close();
    } catch (LuaException& e)
    {
        LOG_ERROR(e.what());
    }

}

