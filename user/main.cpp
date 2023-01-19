// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point
#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#include "detours.h"
#include <random>
#include <string>
#pragma comment(lib, "detours.lib")

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

static int randomSkinId{};
static int randomHatId{};
static int randomPetId{};
static int randomColorId{};

static PlayerControl* LocalPlayer;

void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method)
{
    //std::cout << "Hooked" << std::endl;
    //randomSkinId = rand() % 15;
    //randomHatId = rand() % 93;
    //randomPetId = rand() % 10;
    //randomColorId = rand() % 12;

    //PlayerControl_RpcSetSkin(_this, randomSkinId, method);
    //PlayerControl_RpcSetHat(_this, randomHatId, method);
    //PlayerControl_RpcSetPet(_this, randomPetId, method);
    //PlayerControl_RpcSetColor(_this, randomColorId, method);

    //if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    //{
    //    for (int i = 1; i <= 20; i++)
    //    {
    //        std::string s = std::to_string(i);
    //        app::PlayerControl_RpcSendChat(__this, convert_to_string(s), method);
    //    }
    //}

    //判斷是不是自己
    //if(__this == LocalPlayer)
    //{
    //    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    //        PlayerControl_RpcSetScanner(__this, 1, method);
    //    if (GetAsyncKeyState(VK_NUMPAD4) & 1)
    //        PlayerControl_RpcSetScanner(__this, 0, method);
    //}

    return PlayerControl_FixedUpdate(__this, method);
}

void dShipStatus_RpcEndGame(AmongUsClient* __this, MethodInfo* method)
{
    std::cout << "ShipStatus_RpcEndGame Not End" << std::endl;
}

void dInnerNetServer_EndGame(InnerNetServer* __this, MessageReader* message, InnerNetServer_Player* source, MethodInfo* method)
{
    std::cout << "dInnerNetServer_EndGame Not End" << std::endl;
}

void dGameStartManager_BeginGame(GameStartManager* __this, MethodInfo* method)
{
    std::cout << "Hook BeginGame to Call ReallyBegin" << std::endl;

    return GameStartManager_ReallyBegin(__this, 1, method);
}

void dGameStartManager_Update(GameStartManager* __this, MethodInfo* method)
{
    //std::cout << "GameStartManager" << std::endl;

    if(GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        GameStartManager_ReallyBegin(__this, 1, method);
        std::cout << "GameStartManager_ReallyBegin Called" << std::endl;
    }

    return GameStartManager_Update(__this, method);
}

float dShipStatus_CalculateLightRadius(ShipStatus* __this, MethodInfo* method)
{
    //std::cout << "ShipStatus" << std::endl;
    return 10.f;
    //return ShipStatus_CalculateLightRadius(__this, method);
}

void dLightSource_Update(LightSource* __this, MethodInfo* method)
{
    //std::cout << "Light" << std::endl;
  

    return LightSource_Update(__this, method);
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
    //HOOKFUNC(PlayerControl_FixedUpdate);
    //HOOKFUNC(LightSource_Update);
    HOOKFUNC(ShipStatus_CalculateLightRadius);
    //HOOKFUNC(GameStartManager_Update);
    //HOOKFUNC(ShipStatus_RpcEndGame);
    //HOOKFUNC(GameStartManager_BeginGame);
    
    //HOOKFUNC(InnerNetServer_EndGame);
    
    DetourTransactionCommit();

    while (!GetAsyncKeyState(VK_END))
    {
        if (il2cppi_is_initialized(StatsManager__TypeInfo))
        {
            auto StatsManager = (*StatsManager__TypeInfo)->static_fields->Instance;
            StatsManager->fields.banPoints = 0;
        }

        if (il2cppi_is_initialized(PlayerControl__TypeInfo))
        {
            LocalPlayer = (*PlayerControl__TypeInfo)->static_fields->LocalPlayer;

            if(GetAsyncKeyState(VK_NUMPAD1) & 1)
                LocalPlayer->fields.moveable = 1;
            if (GetAsyncKeyState(VK_NUMPAD2) & 1)
                LocalPlayer->fields.moveable = 0;

        }
        Sleep(20);
    }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //UnHook
    //UNHOOKFUNC(PlayerControl_FixedUpdate);
    //UNHOOKFUNC(LightSource_Update);
    UNHOOKFUNC(ShipStatus_CalculateLightRadius);
    //UNHOOKFUNC(GameStartManager_Update);
    //UNHOOKFUNC(ShipStatus_RpcEndGame);
    //UNHOOKFUNC(GameStartManager_BeginGame);
    //UNHOOKFUNC(InnerNetServer_EndGame);

    DetourTransactionCommit();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}