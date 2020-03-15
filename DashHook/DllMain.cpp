#include "Hooking.h"
#include "Main.h"
#include "Logger.hpp"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH: {
            logger.SetFile("./DashHook.log");
            logger.Clear();
            logger.Write(LogLevel::INFO, "DashHook %s (built %s %s)", "v1.0.0", __DATE__, __TIME__);
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
