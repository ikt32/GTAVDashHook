using System;
using System.IO;
using System.Runtime.InteropServices;
using GTA;
using GTA.Native;

// Copied from the current header, with C# attributes to make it compatible.
[StructLayout(LayoutKind.Sequential, Pack=0, CharSet = CharSet.Ansi)]
public struct VehicleDashboardData
{
    public float RPM; // 0x00
    public float speed; // 0x04
    public float fuel; // 0x08
    public float temp; // 0x0C
    public float vacuum; // 0x10
    public float boost; // 0x14
    public float waterTemp; // 0x18
    public float oilTemperature; // 0x1C
    public float oilPressure; // 0x20
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 0x3F)]
    public byte[] _pad; // 0x24 aircraft data
    [MarshalAs(UnmanagedType.I1)]
    public bool indicator_left; // 0x63
    [MarshalAs(UnmanagedType.I1)]
    public bool indicator_right; // 0x64
    [MarshalAs(UnmanagedType.I1)]
    public bool handbrakeLight; // 0x65
    [MarshalAs(UnmanagedType.I1)]
    public bool engineLight; // 0x66
    [MarshalAs(UnmanagedType.I1)]
    public bool ABSLight; // 0x67
    [MarshalAs(UnmanagedType.I1)]
    public bool petrolLight; // 0x68
    [MarshalAs(UnmanagedType.I1)]
    public bool oilLight; // 0x69
    [MarshalAs(UnmanagedType.I1)]
    public bool headlights; // 0x6A
    [MarshalAs(UnmanagedType.I1)]
    public bool fullBeam; // 0x6B
    [MarshalAs(UnmanagedType.I1)]
    public bool batteryLight; // 0x6C
}

// Load the library when this script is created, and put the functions in
// the DashHookDll namespace.

// If DashHook is optional for your script, consider dynamically loading it in.
// https://gist.github.com/E66666666/d11cdbd9800ad73efeff612374349347 should
// get you going.
static class DashHookDll
{
    [DllImport("DashHook.dll")]
    public static extern void DashHook_GetData(out VehicleDashboardData data);
    
    [DllImport("DashHook.dll")]
    public static extern void DashHook_SetData(VehicleDashboardData data);
}

public class ShowDash : Script
{
    public ShowDash()
    {
        Tick += OnTick;
    }

    private void OnTick(object source, EventArgs e)
    {
        // GetData wants a pointer, so we make our struct outselves, and
        // pass it as an out argument to the function.
        VehicleDashboardData dashData = new VehicleDashboardData();
        DashHookDll.DashHook_GetData(out dashData);
        
        // Now, data can be grabbed. For example, RPM.
        ShowText(0.0f, 0.00f, "DH RPM: " + dashData.RPM);

        // Data can also be set. For example, forcing the indicators to
        // always stay on.
        dashData.indicator_left = true;
        dashData.indicator_right = true;

        // The modified dashData is written back.
        DashHookDll.DashHook_SetData(dashData);
    }

    void ShowText(float x, float y, string text, float size = 0.5f)
    {
        Function.Call(Hash.SET_TEXT_FONT, 0);
        Function.Call(Hash.SET_TEXT_SCALE, size, size);
        Function.Call(Hash.SET_TEXT_COLOUR, 255, 255, 255, 255);
        Function.Call(Hash.SET_TEXT_WRAP, 0.0, 1.0);
        Function.Call(Hash.SET_TEXT_CENTRE, 0);
        Function.Call(Hash.SET_TEXT_OUTLINE, true);
        Function.Call(Hash._SET_TEXT_ENTRY, "STRING");
        Function.Call(Hash._ADD_TEXT_COMPONENT_STRING, text);
        Function.Call(Hash._DRAW_TEXT, x, y);
    }
}