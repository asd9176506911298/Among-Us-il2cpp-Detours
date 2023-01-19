// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#include "detours.h"
#pragma comment(lib, "detours.lib")

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

void dPlayerControl_FixedUpdate(PlayerControl* _this, MethodInfo* method)
{

    //std::cout << "Hooked" << std::endl;

    return PlayerControl_FixedUpdate(_this, method);
}

void dLightSource_Update(LightSource* _this, MethodInfo* method)
{
    //std::cout << "Light" << std::endl;
  
    


    return LightSource_Update(_this, method);
}

float dShipStatus_CalculateLightRadius(ShipStatus* _this, MethodInfo* method)
{
    std::cout << "ShipStatus" << std::endl;
    return 10.f;
    //return ShipStatus_CalculateLightRadius(_this, method);
}

#define HOOKFUNC(n) DetourAttach(&(PVOID&)n, d##n)
#define UNHOOKFUNC(n) DetourDetach(&(PVOID&)n, d##n)

// Custom injected code entry point
void Run(HMODULE hModule)
{
    // Initialize thread data - DO NOT REMOVE
    il2cpp_thread_attach(il2cpp_domain_get());

    // If you would like to write to a log file, specify the name above and use il2cppi_log_write()
    // il2cppi_log_write("Startup");

    // If you would like to output to a new console window, use il2cppi_new_console() to open one and redirect stdout
    // il2cppi_new_console();
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    // Place your custom code here

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //Hook
    HOOKFUNC(PlayerControl_FixedUpdate);
    HOOKFUNC(LightSource_Update);
    HOOKFUNC(ShipStatus_CalculateLightRadius);

    DetourTransactionCommit();

    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(20);
    }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //UnHook
    UNHOOKFUNC(PlayerControl_FixedUpdate);
    UNHOOKFUNC(LightSource_Update);
    UNHOOKFUNC(ShipStatus_CalculateLightRadius);

    DetourTransactionCommit();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}