#pragma once
#include <windows.h>
#include <cstdint>
#include <string>

namespace Cheat {
    uintptr_t GetGameAppInstance();
    uintptr_t GetGameState();
    uintptr_t GetGameScene();
    uintptr_t GetLocalPlayerInstance();

    void AddCash(int amount);
    void AddCrystal(int amount);
    void nametag(std::string);
    void godmod(bool);
    void zombieGun(bool);

    // Fonctions de débogage
    void PrintGameStateInfo();
}