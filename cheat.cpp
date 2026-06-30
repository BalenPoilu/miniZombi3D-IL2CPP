#include "pch-il2cpp.h"
#include "Cheat.h"
#include <iostream>
#include <string>
#include <thread>

uintptr_t Cheat::GetGameAppInstance() {
    const Il2CppDomain* domain = il2cpp_domain_get();
    if (!domain) return 0;

    size_t size = 0;
    const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &size);
    if (!assemblies || size == 0) return 0;

    const Il2CppImage* mainImage = nullptr;
    for (size_t i = 0; i < size; i++) {
        const char* name = il2cpp_image_get_name(il2cpp_assembly_get_image(assemblies[i]));
        if (name && strstr(name, "Assembly-CSharp")) {
            mainImage = il2cpp_assembly_get_image(assemblies[i]);
            break;
        }
    }
    if (!mainImage) mainImage = il2cpp_assembly_get_image(assemblies[0]);
    if (!mainImage) return 0;

    Il2CppClass* klassGameApp = il2cpp_class_from_name(mainImage, "Zombie3D", "GameApp");
    if (!klassGameApp) return 0;

    FieldInfo* fieldInstance = il2cpp_class_get_field_from_name(klassGameApp, "instance");
    if (fieldInstance) {
        uintptr_t instance = 0;
        il2cpp_field_static_get_value(fieldInstance, &instance);
        if (instance) return instance;
    }

    const PropertyInfo* propInstance = il2cpp_class_get_property_from_name(klassGameApp, "Instance");
    if (propInstance) {
        const MethodInfo* getMethod = il2cpp_property_get_get_method(propInstance);
        if (getMethod) {
            uintptr_t instance = (uintptr_t)il2cpp_runtime_invoke(getMethod, nullptr, nullptr, nullptr);
            if (instance) return instance;
        }
    }

    return 0;
}

uintptr_t Cheat::GetGameState() {
    uintptr_t gameApp = GetGameAppInstance();
    if (!gameApp) return 0;

    Il2CppClass* gameAppClass = il2cpp_object_get_class((Il2CppObject*)gameApp);
    if (!gameAppClass) return 0;

    const char* fieldNames[] = { "gameState", "m_gameState", "currentGameState", nullptr };
    for (int i = 0; fieldNames[i] != nullptr; i++) {
        FieldInfo* field = il2cpp_class_get_field_from_name(gameAppClass, fieldNames[i]);
        if (field) {
            uintptr_t gameState = 0;
            il2cpp_field_get_value((Il2CppObject*)gameApp, field, &gameState);
            if (gameState) return gameState;
        }
    }

    return 0;
}

uintptr_t Cheat::GetGameScene() {
    uintptr_t gameApp = GetGameAppInstance();
    if (!gameApp) return 0;

    Il2CppClass* gameAppClass = il2cpp_object_get_class((Il2CppObject*)gameApp);
    if (!gameAppClass) return 0;

    const char* fieldNames[] = { "gameState", "m_gameState", "currentGameState", nullptr };
    for (int i = 0; fieldNames[i] != nullptr; i++) {
        FieldInfo* field = il2cpp_class_get_field_from_name(gameAppClass, fieldNames[i]);
        if (field) {
            uintptr_t gameState = 0;
            il2cpp_field_get_value((Il2CppObject*)gameApp, field, &gameState);
            if (gameState) return gameState;
        }
    }

    return 0;
}

void Cheat::AddCash(int amount) {
    if (amount <= 0) {
        printf("[Erreur] Le montant doit être positif.\n");
        return;
    }

    uintptr_t gameStatePtr = GetGameState();
    if (!gameStatePtr) {
        printf("[Erreur] Impossible d'obtenir GameState.\n");
        return;
    }

    Il2CppClass* gameStateClass = il2cpp_object_get_class((Il2CppObject*)gameStatePtr);
    if (!gameStateClass) {
        printf("[Erreur] Impossible d'obtenir la classe GameState\n");
        return;
    }

    printf("[Debug] Classe GameState: %s\n", il2cpp_class_get_name(gameStateClass));

    FieldInfo* cashField = il2cpp_class_get_field_from_name(gameStateClass, "cash");
    if (cashField) {
        app::SafeInteger* cash = nullptr;
        il2cpp_field_get_value((Il2CppObject*)gameStatePtr, cashField, &cash);
        if (cash) {
            int32_t current = app::SafeInteger_Get(cash, nullptr);
            int32_t newValue = current + amount;
            app::SafeInteger_Set(cash, newValue, nullptr);
            printf("[Succès] Cash: %d -> %d\n", current, newValue);
            return;
        }
    }

    const MethodInfo* addCashMethod = il2cpp_class_get_method_from_name(gameStateClass, "AddCash", 1);
    if (!addCashMethod) {
        addCashMethod = il2cpp_class_get_method_from_name(gameStateClass, "addCash", 1);
    }

    if (addCashMethod) {
        Il2CppClass* safeIntClass = il2cpp_class_from_name(nullptr, "Zombie3D", "SafeInteger");
        if (!safeIntClass) {
            safeIntClass = il2cpp_class_from_name(nullptr, "System", "Int32");
        }

        if (safeIntClass) {
            void* param = nullptr;

            const char* className = il2cpp_class_get_name(safeIntClass);
            if (className && strstr(className, "SafeInteger")) {
                app::SafeInteger* safeInt = (app::SafeInteger*)il2cpp_object_new(safeIntClass);
                if (safeInt) {
                    app::SafeInteger_Set(safeInt, amount, nullptr);
                    param = safeInt;
                }
            }
            else {
                param = &amount;
            }

            if (param) {
                il2cpp_runtime_invoke(addCashMethod, (Il2CppObject*)gameStatePtr, &param, nullptr);
                printf("[Succès] Cash ajouté via AddCash: %d\n", amount);
                return;
            }
        }
    }

    const MethodInfo* addCashMethod2 = il2cpp_class_get_method_from_name(gameStateClass, "AddCash", 2);
    if (addCashMethod2) {
        void* args[2] = { &amount, nullptr };
        il2cpp_runtime_invoke(addCashMethod2, (Il2CppObject*)gameStatePtr, args, nullptr);
        printf("[Succès] Cash ajouté via AddCash (2 params): %d\n", amount);
        return;
    }

    printf("[Erreur] Impossible d'ajouter du cash\n");
}

void Cheat::AddCrystal(int amount) {
    if (amount <= 0) {
        printf("[Erreur] Le montant doit être positif.\n");
        return;
    }

    uintptr_t gameStatePtr = GetGameState();
    if (!gameStatePtr) {
        printf("[Erreur] Impossible d'obtenir GameState.\n");
        return;
    }

    Il2CppClass* gameStateClass = il2cpp_object_get_class((Il2CppObject*)gameStatePtr);
    if (!gameStateClass) {
        printf("[Erreur] Impossible d'obtenir la classe GameState\n");
        return;
    }

    FieldInfo* crystalField = il2cpp_class_get_field_from_name(gameStateClass, "crystal");
    if (crystalField) {
        app::SafeInteger* crystal = nullptr;
        il2cpp_field_get_value((Il2CppObject*)gameStatePtr, crystalField, &crystal);
        if (crystal) {
            int32_t current = app::SafeInteger_Get(crystal, nullptr);
            int32_t newValue = current + amount;
            app::SafeInteger_Set(crystal, newValue, nullptr);
            printf("[Succès] Cristaux: %d -> %d\n", current, newValue);
            return;
        }
    }

    const MethodInfo* addCrystalMethod = il2cpp_class_get_method_from_name(gameStateClass, "AddCrystal", 1);
    if (!addCrystalMethod) {
        addCrystalMethod = il2cpp_class_get_method_from_name(gameStateClass, "addCrystal", 1);
    }

    if (addCrystalMethod) {
        Il2CppClass* safeIntClass = il2cpp_class_from_name(nullptr, "Zombie3D", "SafeInteger");
        if (!safeIntClass) {
            safeIntClass = il2cpp_class_from_name(nullptr, "System", "Int32");
        }

        if (safeIntClass) {
            void* param = nullptr;

            const char* className = il2cpp_class_get_name(safeIntClass);
            if (className && strstr(className, "SafeInteger")) {
                app::SafeInteger* safeInt = (app::SafeInteger*)il2cpp_object_new(safeIntClass);
                if (safeInt) {
                    app::SafeInteger_Set(safeInt, amount, nullptr);
                    param = safeInt;
                }
            }
            else {
                param = &amount;
            }

            if (param) {
                il2cpp_runtime_invoke(addCrystalMethod, (Il2CppObject*)gameStatePtr, &param, nullptr);
                printf("[Succès] Cristaux ajoutés via AddCrystal: %d\n", amount);
                return;
            }
        }
    }

    // 3. Essayer avec 2 paramètres - CORRIGÉ avec const
    const MethodInfo* addCrystalMethod2 = il2cpp_class_get_method_from_name(gameStateClass, "AddCrystal", 2);
    if (addCrystalMethod2) {
        void* args[2] = { &amount, nullptr };
        il2cpp_runtime_invoke(addCrystalMethod2, (Il2CppObject*)gameStatePtr, args, nullptr);
        printf("[Succès] Cristaux ajoutés via AddCrystal (2 params): %d\n", amount);
        return;
    }

    printf("[Erreur] Impossible d'ajouter des cristaux\n");
}

void Cheat::nametag(std::string name) {
    uintptr_t gameStatePtr = GetGameState();
    if (!gameStatePtr) return;

    app::GameState__Fields* gameStateFields = reinterpret_cast<app::GameState__Fields*>(gameStatePtr);
    if (!gameStateFields) return;

    gameStateFields->nick_name = reinterpret_cast<app::String*>(il2cpp_string_new(name.c_str()));
}

void Cheat::godmod(bool stat) {
    while (stat) {
        uintptr_t gameScene = GetGameScene();
        if (!gameScene) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        app::GameScene__Fields* gameSceneFields = reinterpret_cast<app::GameScene__Fields*>(gameScene);
        if (!gameSceneFields || !gameSceneFields->player) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        app::Player__Fields* playerFields = &gameSceneFields->player->fields;

        playerFields->hp = playerFields->maxHp;

        if (playerFields->cur_weapon) {
            app::Weapon__Fields* weaponFields = &playerFields->cur_weapon->fields;
            weaponFields->_enableShoot_k__BackingField = true;
            weaponFields->lastShootTime = 0.0f;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Cheat::zombieGun(bool stat) {
    if (!stat) return;

    uintptr_t gameSceneAddr = GetGameScene();
    app::GameScene__Fields* gameScene = reinterpret_cast<app::GameScene__Fields*>(gameSceneAddr);
    if (!gameScene || !gameScene->enemyList) return;

    app::BaseCameraScript* cameraScript = gameScene->camera;
    if (!cameraScript) return;

    app::Transform* cameraTransform = cameraScript->fields.cameraTransform;
    if (!cameraTransform) return;

    app::Hashtable* enemyTable = reinterpret_cast<app::Hashtable*>(gameScene->enemyList);
    app::Hashtable__Fields fields = enemyTable->fields;

    if (!fields._buckets || fields._count == 0) return;

    for (int i = 0; i < fields._count; i++) {
        auto bucket = fields._buckets->vector[i];

        if (bucket.val == nullptr) continue;

        app::Enemy* enemy = reinterpret_cast<app::Enemy*>(bucket.val);

        app::Vector3 enemyWorldPos = enemy->fields.last_pos;

        app::Vector3 screenPos = app::Camera_WorldToScreenPoint(reinterpret_cast<app::Camera*>(cameraScript), enemyWorldPos, nullptr);

        if (screenPos.z > 0.0f) {

            float screenHeight = app::Screen_get_height(nullptr);
            float drawX = screenPos.x;
            float drawY = screenHeight - screenPos.y;
        }
    }
}

void Cheat::PrintGameStateInfo()
{
    // À implémenter plus tard
}