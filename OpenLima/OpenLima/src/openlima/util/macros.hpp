// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_MACROS_HPP
#define OPENLIMA_UTIL_MACROS_HPP

// Defines of OpenLima:
// 
// Extern defines (Should be defined with compiler definitions):
// OPENLIMA_PRECISE_REAL => Uses "double" instead of "float" for the openlima::util::real type.
// 
// Intern defines (Will be defined by this file):
// OPENLIMA_WIN => Build for Windows
// OPENLIMA_LIN => Build for Linux
// OPENLIMA_OSX => Build for Mac OS X
// OPENLIMA_X64 => Build for x64
// OPENLIMA_X86 => Build for 32-Bit
// OPENLIMA_DLL => Is "__declspec(dllexport)" under windows, else nothing
// OPENLIMA_MAIN => The main-function for the application. Needed to be compatible with
//						/SUBSYSTEM:WINDOWS
// OPENLIMA_REAL_TYPE => Will be the type for openlima::util::real. Use the OPENLIMA_PRECISE_REAL-
//							macro to switch between float and double.
// 
// Additional defines (If not already defined):
// GLUT_WHEEL_UP
// GLUT_WHEEL_DOWN
// BOOST_FOREACH_PAIR

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

//////////////////////////////////////
// OPENLIMA_REAL_TYPE-Macro
#if defined(OPENLIMA_PRECISE_REAL) && !defined(OPENLIMA_REAL_TYPE)
#define OPENLIMA_REAL_TYPE double
#else
#define OPENLIMA_REAL_TYPE float
#endif

#ifndef BOOST_FOREACH_PAIR
#define BOOST_FOREACH_PAIR(KEY, VALUE, COL) BOOST_FOREACH_PREAMBLE() \
if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_col) \
	= BOOST_FOREACH_CONTAIN(COL)) {} else if \
	(boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_cur) = \
	BOOST_FOREACH_BEGIN(COL)) {} else if \
	(boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_end) = \
	BOOST_FOREACH_END(COL)) {} else for (bool \
	BOOST_FOREACH_ID(_foreach_continue) = true, \
	BOOST_FOREACH_ID(_foreach_key_loop) = true; \
BOOST_FOREACH_ID(_foreach_continue) && !BOOST_FOREACH_DONE(COL); \
BOOST_FOREACH_ID(_foreach_continue) ? BOOST_FOREACH_NEXT(COL) : \
	(void)0) if (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_continue))) \
{} else if (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_key_loop))) \
{} else for (KEY = BOOST_FOREACH_DEREF(COL).first; \
!BOOST_FOREACH_ID(_foreach_key_loop); \
BOOST_FOREACH_ID(_foreach_key_loop) = true) for (VALUE = \
	BOOST_FOREACH_DEREF(COL).second; !BOOST_FOREACH_ID(_foreach_continue); \
BOOST_FOREACH_ID(_foreach_continue) = true)
#endif


#endif /* OPENLIMA_UTIL_MACROS_HPP */
