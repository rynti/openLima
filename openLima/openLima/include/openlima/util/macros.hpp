// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_MACROS_HPP
#define OPENLIMA_UTIL_MACROS_HPP

// Defines of openLima:
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
// OPENLIMA_REAL(x) => Can be used to create Real literals with ensuring that on non-precise real
//						the "f" prefix is used.
// OPENLIMA_SIL_WINAPI => Use WinAPI for SIL
// OPENLIMA_SIL_XLIB => Use Xlib for SIL
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
#ifdef _M_X64
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
// OPENLIMA_DLL-macro
#ifdef OPENLIMA_WIN
#define OPENLIMA_DLL __declspec(dllexport)
#else
#define OPENLIMA_DLL
#endif

//////////////////////////////////////
// OPENLIMA_MAIN-macro
#ifdef OPENLIMA_WIN
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
// OPENLIMA_REAL_TYPE-macro
#if defined(OPENLIMA_PRECISE_REAL) && !defined(OPENLIMA_REAL_TYPE)
#define OPENLIMA_REAL_TYPE double
#else
#define OPENLIMA_REAL_TYPE float
#endif

//////////////////////////////////////
// OPENLIMA_REAL(x)-macro
#if OPENLIMA_PRECISE_REAL
#define OPENLIMA_REAL(x) x
#else
#define OPENLIMA_REAL(x) (x ## f)
#endif

//////////////////////////////////////
// SIL-type
#ifdef OPENLIMA_WIN
#define OPENLIMA_SIL_WINAPI
#else
#define OPENLIMA_SIL_XLIB
#endif

//////////////////////////////////////
// GLUT_WHEEL_UP-macro
#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#endif

//////////////////////////////////////
// GLUT_WHEEL_DOWN-macro
#ifndef GLUT_WHEEL_DOWN
#define GLUT_WHEEL_DOWN 4
#endif

//////////////////////////////////////
// BOOST_FOREACH_PAIR-macro

#ifndef BOOST_FOREACH_PAIR
#include <boost/foreach.hpp>

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
