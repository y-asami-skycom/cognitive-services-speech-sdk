// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "debug_utils.h"

using namespace CARBON_IMPL_NAMESPACE();

#ifdef _MSC_VER

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    UNUSED(hModule);
    UNUSED(lpReserved);
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            Debug::HookSignalHandlers();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            CSpxSharedPtrHandleTableManager::Term();
            break;
    }
    return TRUE;
}
#else

__attribute__((constructor)) static void LibLoad(int argc, char** argv, char** envp)
{
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);
    Debug::HookSignalHandlers();
}

__attribute__((destructor)) static void LibUnload()
{
    CSpxSharedPtrHandleTableManager::Term();
}

#endif