#include "pch.h"
#include <iostream>

#define SAMPLE_VALUE_ADDRESS 0x0025E00C
#define SAMPLE_FUNCTION_ADDRESS 0x0024191F

typedef void* (__cdecl* Func2)(int a);

int* intValue = reinterpret_cast<int*>(SAMPLE_VALUE_ADDRESS);
Func2 sampleFunction = reinterpret_cast<Func2>(0x0024191F);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("DLL_PROCESS_ATTACH\n");

        printf("health: %d", *intValue);
        sampleFunction(1000);
        sampleFunction(2000);
        break;
    case DLL_THREAD_ATTACH:
        printf("DLL_THREAD_ATTACH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("DLL_THREAD_DETACH\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("DLL_PROCESS_DETACH\n");
        break;
    }
    return TRUE;
}
