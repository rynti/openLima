// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_SIL_SYSTEMWINDOW_HPP
#define OPENLIMA_SIL_SYSTEMWINDOW_HPP

#include <boost/function.hpp>

#include <map>

#include <openlima/util/macros.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/input/MouseButton.hpp>
#include <openlima/input/KeyboardButton.hpp>

#ifdef OPENLIMA_SIL_XLIB
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif


namespace openlima {
	namespace sil {

		/**
		 * A system window, which means from outside it is system-independent, but internal it
		 * works system-dependent.
		 *
		 * This class is the key feature of SIL.
		 */
		class SystemWindow {
		private:
#ifdef OPENLIMA_SIL_WINAPI
			// WinAPI-only members
			static HINSTANCE hInstance;

			static std::map<HWND, SystemWindow*> registeredWindows;


			HWND hWnd;
			MSG msg;
			WNDCLASS wc;

			HDC hDC;
			HGLRC hRC;

			bool mouseLeaved;


			static LRESULT CALLBACK globalWindowMessageHandler(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT CALLBACK processWindowMessage(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmSystemCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmEraseBackground(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmSizing(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmMouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT wmMouseLeave(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void setupGL();

			void unloadGL();

			void draw();

			void resize(int width, int height);

			bool nextEvent();

#endif

#ifdef OPENLIMA_SIL_XLIB

			static std::map<Window, SystemWindow*> registeredWindows;
			static Display* display;
			static int screen;
			static unsigned long white;
			static unsigned long black;
			static long eventMask;
			static Atom wmDelete;
			static char noData[8];

			Window window;
			Cursor invisibleCursor;
			XSizeHints* sizeHints;
			XVisualInfo* visualInfo;
			GLXContext glContext;


			void mapNotifyEvent(XEvent& evt);

			void configureNotifyEvent(XEvent& evt);

			void motionNotifyEvent(XEvent& evt);

			void buttonReleasedEvent(XEvent& evt);

			void buttonPressedEvent(XEvent& evt);

			void keyReleasedEvent(XEvent& evt);

			void keyPressedEvent(XEvent& evt);

			bool nextEvent(XEvent& evt);

			void setupGL();

			void unloadGL();

			void draw();

			void resize(int width, int height);

#endif

			int width;
			int height;
			const char* title;
			bool cursorVisibility;
			bool visible;
			bool resizable;
			bool alive;

		public:

			/** An event that will be called when the content of this window should get drawn. */
			boost::function<void (SystemWindow&)> drawFunction;

			/** An event that will be called when this window gets resized. */
			boost::function<void (SystemWindow&, int, int)> resizeFunction;

			/** An event that will be called when the mouse of this window was moved. */
			boost::function<void (SystemWindow&, int, int)> mouseMoveFunction;

			/** An event that will be called when a mouse button of this window was clicked. */
			boost::function<void (SystemWindow&, openlima::input::MouseButton, bool)>
				mouseClickFunction;

			/** An event that will be called when a key on the keyboard was pressed. */
			boost::function<void (SystemWindow&, openlima::input::KeyboardButton)> keyDownFunction;

			/** An event that will be called when a key on the keyboard was released. */
			boost::function<void (SystemWindow&, openlima::input::KeyboardButton)> keyUpFunction;


			/**
			 * Creates a new system-independent window.
			 *
			 * @param	title 	The initial title of the window.
			 * @param	width 	The initial width of the window.
			 * @param	height	The initial height of the window.
			 */
			OPENLIMA_DLL SystemWindow(const char* title, int width, int height);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~SystemWindow();


			/**
			 * Executes a step of the main loop.
			 *
			 * @return	True if the main loop is still active, false if any window was closed.
			 */
			OPENLIMA_DLL static bool mainLoopStep();

			/**
			 * Starts the main loop. It basically loops through "mainLoopStep"s as long as that
			 * method returns true.
			 */
			OPENLIMA_DLL static void mainLoop();

			/**
			 * Closes this window.
			 */
			OPENLIMA_DLL void close();

			/**
			 * Hides this window.
			 */
			OPENLIMA_DLL void hide();

			/**
			 * Shows the window.
			 */
			OPENLIMA_DLL void show();

			/**
			 * Returns a value that determines if this window is still "alive".
			 *
			 * @return True if this window is still alive (= Not closed yet), false if not.
			 */
			OPENLIMA_DLL bool isAlive();

			/**
			 * Returns a value that determines if this window is visible.
			 *
			 * @return True if this window is visible, false if not.
			 */
			OPENLIMA_DLL bool isVisible();

			/**
			 * Swap buffers. (Needed for doublebuffering)
			 */
			OPENLIMA_DLL void swapBuffers();

			/**
			 * Sets the mouse position.
			 *
			 * @param	x	The x coordinate, relative to the window.
			 * @param	y	The y coordinate, relative to the window.
			 */
			OPENLIMA_DLL void setMousePosition(int x, int y);

			/**
			 * Sets the mouse visibility.
			 *
			 * @param	visible	True to show, false to hide.
			 */
			OPENLIMA_DLL void setMouseVisibility(bool visible);

			/**
			 * Returns a value that determines if the mouse of this window is visible.
			 *
			 * @return	True if the mouse is visible, or false if not.
			 */
			OPENLIMA_DLL bool isMouseVisible();

			/**
			 * Sets the window size.
			 * The size is a so-called "client size", which means it is without any window frames,
			 * etc.!
			 *
			 * @param	width 	The width.
			 * @param	height	The height.
			 */
			OPENLIMA_DLL void setSize(int width, int height);

			/**
			 * Sets the window title.
			 *
			 * @param	title	The window title.
			 */
			OPENLIMA_DLL void setTitle(const char* title);

			/**
			 * Returns the title of this window.
			 *
			 * @return The title of this window.
			 */
			OPENLIMA_DLL const char* getTitle();

			/**
			 * Makes this window resizable or unresizable, depending on the given value.
			 *
			 * @param	resizable	True to make this window resizable, else false.
			 */
			OPENLIMA_DLL void setResizable(bool resizable);

			/**
			 * Returns a value, that determines if this window is resizable or not.
			 *
			 * @return True if this window is resizable, false if not.
			 */
			OPENLIMA_DLL bool isResizable();

			/**
			 * Returns the window width.
			 *
			 * @return	The window width.
			 */
			OPENLIMA_DLL int getWidth();

			/**
			 * Returns the window height.
			 *
			 * @return	The window height.
			 */
			OPENLIMA_DLL int getHeight();

		};

	}
}

#endif /* OPENLIMA_SIL_SYSTEMWINDOW_HPP */
