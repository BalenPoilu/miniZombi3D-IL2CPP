#include "pch-il2cpp.h"
#include "Cheat.h"
#include "ConsoleManager.h"
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <conio.h>

extern bool bRunning;

bool godmode = false;
bool zombiGun = false;

void ConsoleReaderThread(HMODULE hModule) {
    std::string line = "";
    printf("[Console] Prêt. Saisissez une commande. (F2 pour décharger)\n");
    printf("[Console] Commandes disponibles: addcash <montant> | addcrystal <montant> | max | help\n");

    while (bRunning) {
        if (GetAsyncKeyState(VK_F2) & 0x8000) {
            printf("[Console] Demande d'unload reçue...\n");
            bRunning = false;
            break;
        }

        if (_kbhit()) {
            char ch = _getch();

            if (ch == '\r') {
                std::cout << std::endl;
                if (!line.empty()) {
                    line.erase(line.find_last_not_of(" \n\r\t") + 1);
                }

                printf("[Debug] Commande reçue: '%s'\n", line.c_str());

                if (line.substr(0, 7) == "addcash") {
                    try {
                        int val = std::stoi(line.substr(8));
                        printf("[Debug] Tentative d'ajout de %d cash\n", val);
                        Cheat::AddCash(val);
                        printf("[Debug] Commande addcash exécutée\n");
                    }
                    catch (const std::exception& e) {
                        printf("[Erreur] Exception dans addcash: %s\n", e.what());
                    }
                    catch (...) {
                        printf("[Erreur] Exception inconnue dans addcash\n");
                    }
                }
                else if (line.substr(0, 10) == "addcrystal") {
                    try {
                        int val = std::stoi(line.substr(11));
                        printf("[Debug] Tentative d'ajout de %d cristaux\n", val);
                        Cheat::AddCrystal(val);
                        printf("[Debug] Commande addcrystal exécutée\n");
                    }
                    catch (const std::exception& e) {
                        printf("[Erreur] Exception dans addcrystal: %s\n", e.what());
                    }
                    catch (...) {
                        printf("[Erreur] Exception inconnue dans addcrystal\n");
                    }
                }
                else if (line == "max") {
                    printf("[Debug] Exécution de la commande max\n");
                    Cheat::AddCash(9999999);
                    Cheat::AddCrystal(999999);
                    printf("[Debug] Commande max exécutée\n");
                }
                else if (line == "godmod") {
                    if (godmode) godmode = false;
                    else godmode = true;
					Cheat::godmod(godmode);
                }
                else if (line == "zombigun") {
                    if (zombiGun) zombiGun = false;
                    else zombiGun = true;
                    Cheat::godmod(zombiGun);
                }
                else if (line == "help") {
                    printf("[HELP] \n\taddcash somme\n\taddcrystal somme\n\tmax\n\tgodmod\n\thelp");
                }
                else if (line.substr(0, 7) == "nametag"){
					try {
						std::string name = line.substr(8);
						printf("[Debug] Tentative de changement de nom en '%s'\n", name.c_str());
						Cheat::nametag(name);
						printf("[Debug] Commande nametag exécutée\n");
					}
					catch (const std::exception& e) {
						printf("[Erreur] Exception dans nametag: %s\n", e.what());
					}
					catch (...) {
						printf("[Erreur] Exception inconnue dans nametag\n");
					}
                }
                else if (!line.empty()) {
                    printf("[Console] Commande inconnue: '%s'. Tapez 'help' pour la liste.\n", line.c_str());
                }
                line.clear();
            }
            else if (ch == '\b') {
                if (!line.empty()) {
                    line.pop_back();
                    std::cout << "\b \b";
                }
            }
            else {
                line += ch;
                std::cout << ch;
            }
        }
        Sleep(20);
    }

    printf("[Console] Arrêt du thread de lecture...\n");
    fclose(stdout);
    fclose(stdin);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

void InitConsole(HMODULE hModule) {
    std::thread(ConsoleReaderThread, hModule).detach();
}