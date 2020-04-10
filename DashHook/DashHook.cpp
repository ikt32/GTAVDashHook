#include "DashHook-Extended.h"

#include "Logger.hpp"
#include "Pattern.h"
#include "Hooking.h"

#include <Windows.h>
#include <intrin.h>
#include <vector>

// From Unknown
// 48 8B F2 4C 8B F1 E8 ? ? ? ? 48 8B C8 - 0x17
//void(*VehicleDashboardHandler)(void* modelInfo, VehicleDashboardData* data);

typedef void (*VehicleDashboardHandler_t)(void* modelInfo, VehicleDashboardData* data);
CallHook<VehicleDashboardHandler_t>* g_VehicleDashboardHandlerHook = nullptr;

std::vector<HMODULE> g_UserHandles;

bool g_UseCustomDashData;
VehicleDashboardData g_OrigDashData;
VehicleDashboardData g_CustomDashData{};

void DashHook_GetDataOriginal(VehicleDashboardData* data) {
    *data = g_OrigDashData;
}

void DashHook_GetData(VehicleDashboardData* data) {
    if (g_UseCustomDashData)
        *data = g_CustomDashData;
    else
        *data = g_OrigDashData;
}

void DashHook_SetData(VehicleDashboardData data) {
    HMODULE hmod;
    if (RtlPcToFileHeader(_ReturnAddress(), (void**)&hmod))
    {
        if (std::find(g_UserHandles.begin(), g_UserHandles.end(), hmod) == g_UserHandles.end()) {
            WCHAR sz[MAX_PATH];
            if (GetModuleFileName(hmod, sz, MAX_PATH))
            {
                logger.Write(LogLevel::INFO, "[%p] %S", hmod, sz);
            }
            g_UserHandles.push_back(hmod);
        }
    }
    g_UseCustomDashData = true;
    g_CustomDashData = data;
}

VehicleDashboardData applyDelta(VehicleDashboardData current,
    VehicleDashboardData prev,
    VehicleDashboardData prevMod) {

    for (uint32_t offset = 0; offset < sizeof(VehicleDashboardData); ++offset) {
        uint8_t prevByte = *(reinterpret_cast<uint8_t*>(&prev) + offset);
        uint8_t prevModByte = *(reinterpret_cast<uint8_t*>(&prevMod) + offset);
        if (prevByte != prevModByte)
            *(reinterpret_cast<uint8_t*>(&current) + offset) = prevModByte;
    }
    return current;
}

void DashboardHandler(void* modelInfo, VehicleDashboardData* data) {
    VehicleDashboardData lastDashData = g_OrigDashData;
    if (data) {
        g_OrigDashData = *data;
    }
    if (g_UseCustomDashData) {
        auto delta = applyDelta(g_OrigDashData, lastDashData, g_CustomDashData);
        g_VehicleDashboardHandlerHook->fn(modelInfo, &delta);
    }
    else {
        g_VehicleDashboardHandlerHook->fn(modelInfo, data);
    }
    g_UseCustomDashData = false;
}

void setupHooks() {
    auto addr = Pattern::FindPattern("\x48\x8B\x4F\x20\x48\x8D\x54\x24\x00\xE8", "xxxxxxxx?x");
    if (!addr) {
        logger.Write(LogLevel::ERROR, "Couldn't find VehicleDashboardHandler");
        return;
    }
    logger.Write(LogLevel::INFO, "Found VehicleDashboardHandler at 0x%p", addr);
    g_VehicleDashboardHandlerHook = HookManager::SetCall(addr + 0x09, DashboardHandler);
}

void removeHooks() {
    if (g_VehicleDashboardHandlerHook) {
        g_VehicleDashboardHandlerHook->remove();
        delete g_VehicleDashboardHandlerHook;
        g_VehicleDashboardHandlerHook = nullptr;
    }
}
