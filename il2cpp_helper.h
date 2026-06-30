#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

template <typename T>
T* FindStaticInstance(const char* namespaze, const char* className, const char* fieldName)
{
    // Récupération dynamique de la fonction interne d'Unity
    typedef void (*il2cpp_field_static_get_value_t)(FieldInfo* field, void* value);
    il2cpp_field_static_get_value_t get_static_value = (il2cpp_field_static_get_value_t)GetProcAddress(GetModuleHandleA("GameAssembly.dll"), "il2cpp_field_static_get_value");

    if (!get_static_value) return nullptr;

    // Utilisation des API globales déjà fournies par Il2CppInspector
    const Il2CppDomain* domain = il2cpp_domain_get();
    size_t size = 0;
    const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &size);
    if (size == 0 || !assemblies) return nullptr;

    const Il2CppImage* mainImage = il2cpp_assembly_get_image(assemblies[0]);
    if (!mainImage) return nullptr;

    Il2CppClass* klass = il2cpp_class_from_name(mainImage, namespaze, className);
    if (!klass) return nullptr;

    FieldInfo* field = il2cpp_class_get_field_from_name(klass, fieldName);
    if (!field) return nullptr;

    void* staticInstance = nullptr;
    get_static_value(field, &staticInstance);

    return (T*)staticInstance;
}