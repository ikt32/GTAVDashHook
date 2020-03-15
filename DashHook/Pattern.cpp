#include "Pattern.h"

#include <Windows.h>
#include <Psapi.h>
#include <cstring>

uintptr_t Pattern::FindPattern(const char* pattern, const char* mask) {
    MODULEINFO modInfo = {nullptr};
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

    const char* start_offset = reinterpret_cast<const char*>(modInfo.lpBaseOfDll);
    const uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);

    intptr_t pos = 0;
    const uintptr_t searchLen = static_cast<uintptr_t>(strlen(mask) - 1);

    for (const char* retAddress = start_offset; retAddress < start_offset + size; retAddress++) {
        if (*retAddress == pattern[pos] || mask[pos] == '?') {
            if (mask[pos + 1] == '\0')
                return (reinterpret_cast<uintptr_t>(retAddress) - searchLen);
            pos++;
        }
        else {
            pos = 0;
        }
    }
    return 0;
}
