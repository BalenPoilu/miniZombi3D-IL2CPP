#include "pch-il2cpp.h"
#include "../Cheat.h"
#include "../ConsoleManager.h"
#include "../framework/helpers.h"
#include <thread>
#include <chrono>

extern const wchar_t* const LOG_FILE = L"il2cpp-log.txt";
bool bRunning = true;

DWORD WINAPI Run(LPVOID lpParam) {
    HMODULE hModule = (HMODULE)lpParam;

    printf("[Bypass] Attachement au domaine Il2Cpp...\n");
    il2cpp_thread_attach(il2cpp_domain_get());
    printf("[Bypass] Attachement réussi\n");

    printf("[Bypass] Création de la console...\n");
    il2cppi_new_console();
    printf("[Bypass] Console créée\n");

    printf("[Bypass] Initialisation de la console de commandes...\n");
    InitConsole(hModule);
    printf("[Bypass] Console de commandes initialisée\n");

    printf("\n========================================\n");
    printf("  Bypass chargé avec succès!\n");
    printf("  Tapez 'help' pour la liste des commandes\n");
    printf("  Appuyez sur F2 pour décharger\n");
    printf("========================================\n\n");

    // Afficher les informations sur GameState au démarrage
    Cheat::PrintGameStateInfo();

    printf("[Bypass] Système prêt. Utilisez les commandes de la console.\n");

    while (bRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    printf("[Bypass] Arrêt du thread principal...\n");
    return 0;
}