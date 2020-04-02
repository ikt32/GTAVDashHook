#ifndef DASHHOOK_H
#define DASHHOOK_H

#ifdef DASHHOOK_EXPORTS
#define DASHHOOK_API extern "C" __declspec(dllexport)

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define VER_MAJOR 1
#define VER_MINOR 0
#define VER_PATCH 0

#define DASHHOOK_VER STR(VER_MAJOR) "."  STR(VER_MINOR) "." STR(VER_PATCH)
#else
#ifndef DASHHOOK_RUNTIME
#define DASHHOOK_API extern "C" __declspec(dllimport)
#else
// noop
#define DASHHOOK_API
#endif
#endif

struct VehicleDashboardData
{
    float RPM; // 0x00
    float speed; // 0x04
    float fuel; // 0x08
    float temp; // 0x0C
    float vacuum; // 0x10
    float boost; // 0x14
    float waterTemp; // 0x18
    float oilTemperature; // 0x1C
    float oilPressure; // 0x20
    char _pad[0x3F]; // 0x24 aircraft data
    bool indicator_left; // 0x63
    bool indicator_right; // 0x64
    bool handbrakeLight; // 0x65
    bool engineLight; // 0x66
    bool ABSLight; // 0x67
    bool petrolLight; // 0x68
    bool oilLight; // 0x69
    bool headlights; // 0x6A
    bool fullBeam; // 0x6B
    bool batteryLight; // 0x6C
};

/**
 * \brief               Get the current dashboard data.
 * \param data [out]    A pointer to a VehicleDashboardData struct.
 */
DASHHOOK_API void DashHook_GetData(VehicleDashboardData* data);

/**
 * \brief   Set the dashboard data to be shown next tick.
 * \param[in] data The dashboard data.
 */
DASHHOOK_API void DashHook_SetData(VehicleDashboardData data);

#endif
