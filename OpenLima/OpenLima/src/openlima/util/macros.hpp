#ifndef OPENLIMA_UTIL_MACROS_HPP
#define OPENLIMA_UTIL_MACROS_HPP


// Defines of OpenLima:
// Extern defines (Should be defined as early as possible):
// 
// Intern defines (Will be defined by this file):
// L_WIN => Build for Windows
// L_LIN => Build for Linux
// L_OSX => Build for Mac OS X
// L_X64 => Build for x64
// L_X86 => Build for 32-Bit
// L_DLL => Is "__declspec(dllexport)" under windows, else nothing
// L_MAIN => The main-function for the application. Under windows without explicit L_WIN_SUBSYSTEM_CONSOLE it's WinMain.

//////////////////////////////////////
// Operating system macros
// Windows:
#ifdef _WIN32
#define L_WIN
#ifdef _WIN64
#define L_X64
#else
#define L_X86
#endif
#endif

// Mac OS X:
#ifdef __APPLE__
#define L_OSX
#define L_X64
#endif

// Linux:
#if defined(__linux) || defined(linux)
#define L_LIN
#if defined(__LP64__) || defined(_LP64)
#define L_X64
#else
#define L_X86
#endif
#endif

//////////////////////////////////////
// L_DLL-Macro
#ifdef L_WIN
#define L_DLL __declspec(dllexport)
#else
#define L_DLL
#endif

// L_MAIN-Macro
#if defined(L_WIN)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#define L_MAIN(c, v) int main(c,v); int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { return main(__argc, __argv); } int main(c, v)

#else

#define L_MAIN(c, v) int main(c, v)
#define L_MAIN(c, v) int main(c, v)
#endif


#endif /* OPENLIMA_UTIL_MACROS_HPP */