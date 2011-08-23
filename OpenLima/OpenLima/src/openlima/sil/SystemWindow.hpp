// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_SIL_SYSTEMWINDOW_HPP
#define OPENLIMA_SIL_SYSTEMWINDOW_HPP

#include <boost/function.hpp>

#include <map>

#include "../util/macros.hpp"
#include "../input/MouseButton.hpp"
#include "../input/KeyboardButton.hpp"


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
#ifdef OPENLIMA_WIN
			// WinAPI-only members
			static HINSTANCE hInstance;

			static std::map<HWND, SystemWindow*> registeredWindows;


			HWND hWnd;
			MSG msg;
			WNDCLASS wc;

			HDC hDC;
			HGLRC hRC;

			int width;
			int height;

			bool cursorVisibility;
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

#endif

			/**
			 * Executes the next event.
			 *
			 * @return	True if everything is still fine, false if this window was closed.
			 */
			bool nextEvent();

		public:

			/** An event that will be called when the content of this window should get drawn. */
			boost::function<void (SystemWindow&)> onDraw;

			/** An event that will be called when this window gets resized. */
			boost::function<void (SystemWindow&, int, int)> onResize;

			/** An event that will be called when the mouse of this window was moved. */
			boost::function<void (SystemWindow&, int, int)> onMouseMove;

			/** An event that will be called when a mouse button of this window was clicked. */
			boost::function<void (SystemWindow&, openlima::input::MouseButton, bool)> onMouseClick;

			/** An event that will be called when a key on the keyboard was pressed. */
			boost::function<void (SystemWindow&, openlima::input::KeyboardButton)> onKeyDown;

			/** An event that will be called when a key on the keyboard was released. */
			boost::function<void (SystemWindow&, openlima::input::KeyboardButton)> onKeyUp;


			/**
			 * Creates a new system-independent window.
			 *
			 * @param	title 	The initial title of the window.
			 * @param	width 	The initial width of the window.
			 * @param	height	The initial height of the window.
			 */
			OPENLIMA_DLL SystemWindow(const wchar_t* title, int width, int height);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~SystemWindow();


			/**
			 * Shows the window.
			 */
			OPENLIMA_DLL void showWindow();

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
			OPENLIMA_DLL void setTitle(const wchar_t* title);

			/**
			 * Makes this window resizable or unresizable, depending on the given value.
			 *
			 * @param	resizable	True to make this window resizable, else false.
			 */
			OPENLIMA_DLL void setResizable(bool resizable);

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

		};

	}
}

#endif /* OPENLIMA_SIL_SYSTEMWINDOW_HPP */
