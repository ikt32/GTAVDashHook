# DashHook

This library for Grand Theft Auto V allows interaction with the current vehicles' dashboard.

## End User Requirements

* Grand Theft Auto V (v1868+)

## Development

Check `DashHook.h` for the three functions. Recommended to load library runtime if your mod doesn't solely rely on this library.

Usage:

1. Use `DashHook_GetData` to get the current struct.
2. Change whatever value you're interested in.
3. Use `DashHook_SetData` with the edited struct.

## Installation

Simply extract DashHook.dll into the Grand Theft Auto V main folder. Scripts using this library will automatically call it.

