#include "Hooking.h"
#include "Main.h"
#include "Logger.hpp"
#include "DashHook.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH: {
            logger.SetFile("./DashHook.log");
            logger.Clear();
            logger.Write(LogLevel::INFO, "DashHook v%s (built %s %s)", DASHHOOK_VER, __DATE__, __TIME__);
            setupHooks();
            break;
        }
        case DLL_PROCESS_DETACH: {
            removeHooks();
            break;
        }
    }
    return TRUE;
}
