#pragma once
#include <iostream>

// Si estamos en modo Debug (Visual Studio usa _DEBUG, GCC/Clang usan por defecto omitir NDEBUG)
#ifdef _DEBUG
    // Macro que imprime el archivo, la línea y el mensaje
#define ENGINE_INFO(msg) std::cout << "[INFO] " << msg << "\n"
#define ENGINE_LOG(msg) std::cout << "[LOG] " << msg << "\n"
#define ENGINE_WARN(msg) std::cout << "[WARN] " << msg << "\n"
#define ENGINE_ERROR(msg) std::cout << "[ERROR] " << msg << "\n"
#else
    // En Release, estas macros se reemplazan por "nada", el compilador las borra
#define ENGINE_INFO(msg)
#define ENGINE_LOG(msg)
#define ENGINE_WARN(msg)
#define ENGINE_ERROR(msg)
#endif