#ifndef OPENLIMA_UTIL_MACROS_HPP
#define OPENLIMA_UTIL_MACROS_HPP


// Defines of OpenLima:
// Intern defines (Will be defined by this file):
// OPENLIMA_WIN => Build for Windows
// OPENLIMA_LIN => Build for Linux
// OPENLIMA_OSX => Build for Mac OS X
// OPENLIMA_X64 => Build for x64
// OPENLIMA_X86 => Build for 32-Bit
// OPENLIMA_DLL => Is "__declspec(dllexport)" under windows, else nothing
// OPENLIMA_MAIN => The main-function for the application. Needed to be compatible with
//						/SUBSYSTEM:WINDOWS
// 
// Additional defines:
// GLUT_WHEEL_UP   => If not already defined (Compatibility reasons)
// GLUT_WHEEL_DOWN => If not already defined (Compatibility reasons)

//////////////////////////////////////
// Operating system macros
// Windows:
#ifdef _WIN32
#define OPENLIMA_WIN
#ifdef _WIN64
#define OPENLIMA_X64
#else
#define OPENLIMA_X86
#endif
#endif

// Mac OS X:
#ifdef __APPLE__
#define OPENLIMA_OSX
#define OPENLIMA_X64
#endif

// Linux:
#if defined(__linux) || defined(linux)
#define OPENLIMA_LIN
#if defined(__LP64__) || defined(_LP64)
#define OPENLIMA_X64
#else
#define OPENLIMA_X86
#endif
#endif

//////////////////////////////////////
// L_DLL-Macro
#ifdef OPENLIMA_WIN
#define OPENLIMA_DLL __declspec(dllexport)
#else
#define OPENLIMA_DLL
#endif

//////////////////////////////////////
// L_MAIN-Macro
#ifdef OPENLIMA_WIN

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#define OPENLIMA_MAIN(c, v) \
	int main(c,v); \
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, \
		LPSTR lpCmdLine, int nCmdShow) \
	{ \
		return main(__argc, __argv); \
	} \
	int main(c, v)

#else

#define OPENLIMA_MAIN(c, v) int main(c, v)
#endif

//////////////////////////////////////
// GLUT_WHEEL_UP-Macro
#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#endif

//////////////////////////////////////
// GLUT_WHEEL_DOWN-Macro
#ifndef GLUT_WHEEL_DOWN
#define GLUT_WHEEL_DOWN 4
#endif


#endif /* OPENLIMA_UTIL_MACROS_HPP */