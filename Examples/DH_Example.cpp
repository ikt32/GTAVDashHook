// Example of dynamically loading DashHook.

#include "Compatibility.h"

#include <GTAVDashHook/DashHook/DashHook.h>

#include <Windows.h>
#include <string>

namespace {
    bool g_DashHookLoadLibbed = false;
    HMODULE g_DashHookModule = nullptr;

    // Make some function pointers
    void(*g_DashHook_GetData)(VehicleDashboardData*);
    void(*g_DashHook_SetData)(VehicleDashboardData);
}

namespace Dll {
    // Just a helper function to get function pointers.
    template <typename T>
    T CheckAddr(HMODULE lib, const std::string& funcName)
    {
        FARPROC func = GetProcAddress(lib, funcName.c_str());
        if (!func)
        {
            // Error handling
            return nullptr;
        }
        return reinterpret_cast<T>(func);
    }
}

// Provide our own implementations of DashHook.h functions,
// that call the original functions in the library.
void DashHook_GetData(VehicleDashboardData* data) {
    if (g_DashHook_GetData) {
        g_DashHook_GetData(data);
    }
}

void DashHook_SetData(VehicleDashboardData data) {
    if (g_DashHook_SetData) {
        g_DashHook_SetData(data);
    }
}

// Get the functions from the library. If the .dll hasn't been loaded
// by some other script yet, this will load it.
void setupDashHook() {
    g_DashHookLoadLibbed = false;
    g_DashHookModule = GetModuleHandle(L"DashHook.dll");
    if (!g_DashHookModule) {
        g_DashHookModule = LoadLibrary(L"DashHook.dll");
        if (!g_DashHookModule) {
            // Error handling
            return;
        }
        g_DashHookLoadLibbed = true;
    }

    // Set the function pointers
    g_DashHook_GetData = Dll::CheckAddr<void(*)(VehicleDashboardData*)>(g_DashHookModule, "DashHook_GetData");
    g_DashHook_SetData = Dll::CheckAddr<void(*)(VehicleDashboardData)>(g_DashHookModule, "DashHook_SetData");
}

// Call this somewhere before the update loop.
void setupCompatibility() {
    setupDashHook();
    // If setup was successful, DashHook_GetData/DashHook_SetData can be used.
}

// Call this when your script is quitting/unloading.
void releaseCompatibility() {
    if (g_DashHookLoadLibbed) {
        if (FreeLibrary(g_DashHookModule)) {
            g_DashHookModule = nullptr;
        }
        else {
            // Error handling
        }
    }
    g_DashHook_GetData = nullptr;
    g_DashHook_SetData = nullptr;
}
