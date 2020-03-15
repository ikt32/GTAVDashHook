# DashHook

This library for Grand Theft Auto V allows interaction with the current vehicles' dashboard.

## End User Requirements

* Grand Theft Auto V (v1868+)

## Development

Check `DashHook.h` for the three functions. Recommended to load library runtime if your mod doesn't solely rely on this library.

Usage recommendation:

1. Use `DashHook_GetDataCurrent` to get the current struct.
2. Change whatever value you're interested in.
3. Use `DashHook_SetData` with the edited struct.

Do ***not*** use `DashHook_GetDataOriginal` to pass onto the SetData, as it will overwrite any changes called prior to your usage. GetCurrentData will return the struct as the previous caller set it.

There is no access/priority control. It will use the last change from whatever script changed the data last.

