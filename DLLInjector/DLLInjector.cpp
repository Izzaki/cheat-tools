#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <array>
#include "DLLInjector.h"

DWORD GetProcId(const std::wstring procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (std::wstring(procEntry.szExeFile) == procName)
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

bool checkParameters(int count, char* arguments[])
{
    if (count > 1) {
        printf("Dll path: %s\n", arguments[1]);
    }

    if (count > 2) {
        printf("Exe name: %s\n", arguments[2]);
    }

    if (count < 3) {
        printf("Missing some parameters.\n");
        return false;
    }

    return true;
}

int main(int count, char* arguments[])
{
    if (!checkParameters(count, arguments)) {
        return EXIT_FAILURE;
    }

    const char* dllPath = arguments[1];
    const char* exeName = arguments[2];
    const std::wstring procName(&exeName[0], &exeName[strlen(exeName)]); // necessary conversion :d

    DWORD procId = 0;

    printf("Waiting for process to inject.\n");

    while (!procId)
    {
        procId = GetProcId(procName);
        Sleep(1000);
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* memoryLocation = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        WriteProcessMemory(hProc, memoryLocation, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, memoryLocation, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
            printf("Dll has been injected.\n");
        }
    }

    if (hProc)
    {
        CloseHandle(hProc);
    }
    return EXIT_SUCCESS;
}
