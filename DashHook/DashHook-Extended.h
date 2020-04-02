#ifndef DASHHOOK_EXTENDED_H
#define DASHHOOK_EXTENDED_H

#include "DashHook.h"

/**
 * \brief               Get the original unmodified dashboard data.
 *
 *                      This is basically just a dev help, to prevent
 *                      users from the lib accidentally using the wrong function
 *                      and overwriting it all.
 * \param data [out]    A pointer to a VehicleDashboardData struct.
 */
DASHHOOK_API void DashHook_GetDataOriginal(VehicleDashboardData* data);

#endif