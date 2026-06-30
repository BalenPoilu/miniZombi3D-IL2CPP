#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "il2cpp-init.h"
#include "main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        printf("[DLL] DLL_PROCESS_ATTACH\n");
        init_il2cpp();
        printf("[DLL] Il2Cpp initialisé\n");
        CreateThread(NULL, 0, Run, (LPVOID)hModule, 0, NULL);
        printf("[DLL] Thread créé\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("[DLL] DLL_PROCESS_DETACH\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("[DLL] DLL_THREAD_ATTACH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("[DLL] DLL_THREAD_DETACH\n");
        break;
    }
    return TRUE;
}