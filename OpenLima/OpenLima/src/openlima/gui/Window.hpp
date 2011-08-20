// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GUI_WINDOW_HPP
#define OPENLIMA_GUI_WINDOW_HPP

#include <boost/date_time.hpp>

#include <map>

#include "../util/macros.hpp"
#include "../util/types.hpp"
#include "../sil/SystemWindow.hpp"
#include "../input/Mouse.hpp"
#include "../input/MouseMoveEvent.hpp"
#include "../input/Keyboard.hpp"
#include "../input/KeyboardEvent.hpp"


namespace openlima {
	namespace gui {

		/**
		 * A window, that can be rendered and uses functionality of openlima::input to provide easy
		 * use of input devices. Also provides methods like render or update, with built-in time
		 * management and render/update limit.
		 * 
		 * Be sure to use Window::initialize(int*, char**) before constructing a Window-object.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class Window {
		private:

			/** The default update time. */
			static const openlima::util::dtime defaultUpdateTime;


			/** The SystemWindow this window is based on. */
			openlima::sil::SystemWindow* systemWindow;

			/** The time when the previous update happened. */
			boost::posix_time::ptime previousUpdate;

			/** Target time per update. */
			openlima::util::dtime updateTime;

			/** The elapsed time since the last update. */
			openlima::util::dtime updateDelta;

			/** Target time per redraw. */
			openlima::util::dtime redrawTime;

			/** The elapsed time since the last redraw. */
			openlima::util::dtime redrawDelta;

			/**
			 * Determines if redraws are limited.
			 * (If false, redrawTime and redrawDelta are useless)
			 */
			bool limitRedraw;

			/** The mouse for this window. */
			openlima::input::Mouse* mouse;

			/** The keyboard for this window. */
			openlima::input::Keyboard* keyboard;

		protected:

			/**
			 * Creates a new window.
			 * Be sure to call "Window::initialize(int*, char**)" first.
			 *
			 * @param	title	   	The title of the window.
			 * @param	width	   	The width of the window.
			 * @param	height	   	The height of the window.
			 */
			OPENLIMA_DLL Window(const wchar_t* title, int width, int height);


			/**
			 * The resize handler.
			 *
			 * @param	width 	The new window width.
			 * @param	height	The new window height.
			 */
			OPENLIMA_DLL virtual void onResize(openlima::sil::SystemWindow& window,
				int width, int height);

			/**
			 * The draw handler.
			 */
			OPENLIMA_DLL virtual void onDraw(openlima::sil::SystemWindow& window);

		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Window();


			/**
			 * Hides the console. (If there is one)
			 */
			OPENLIMA_DLL static void hideConsole();

			/**
			 * Sets a window dependency mode.
			 *
			 * @param	dependent	(optional) Determines if the windows are dependent of each
			 * 						other. When true, the whole program will stop when any of the
			 * 						windows gets closed, when false, the program will continue
			 * 						execution if any other window is still open.
			 */
			// TODO OPENLIMA_DLL static void setWindowDependency(bool dependent = true);

			/**
			 * Enters the main loop.
			 */
			OPENLIMA_DLL static void enterMainLoop();


			/**
			 * Returns the mouse for this window.
			 *
			 * @return	The mouse for this window.
			 */
			OPENLIMA_DLL openlima::input::Mouse* getMouse();

			/**
			 * Returns the keyboard for this window.
			 *
			 * @return	The keyboard for this window.
			 */
			OPENLIMA_DLL openlima::input::Mouse* getKeyboard();

			/**
			 * Shows the window.
			 */
			OPENLIMA_DLL void showWindow();

			/**
			 * Sets the title of this window.
			 *
			 * @param	title	The title.
			 */
			OPENLIMA_DLL void setTitle(const wchar_t* title);

			/**
			 * Sets the size of this window.
			 *
			 * @param	width 	The new window width.
			 * @param	height	The new window height.
			 */
			OPENLIMA_DLL void setSize(int width, int height);

			/**
			 * Makes this window resizable or unresizable, depending on the given value.
			 *
			 * @param	resizable	True to make this window resizable, else false.
			 */
			OPENLIMA_DLL void setResizable(bool resizable);

			/**
			 * Sets the target render rate.
			 *
			 * @param	rate	The target rate in FPS (=Frames per second).
			 * 					When rate <= 0 then the render limit is disabled, so it will always
			 * 					be re-rendered when it's able to.
			 */
			OPENLIMA_DLL void setRenderRate(openlima::util::Real rate);

			/**
			 * Sets the target update rate.
			 *
			 * @param	rate	The target rate in UPS (=Updates per second).
			 */
			OPENLIMA_DLL void setUpdateRate(openlima::util::Real rate);

			/**
			 * Initializes the rendering.
			 * Be sure to call "finishRendering()" when the rendering is done.
			 */
			OPENLIMA_DLL void initializeRendering();

			/**
			 * Finishes the rendering.
			 */
			OPENLIMA_DLL void finishRendering();


			/**
			 * Will be called when the mouse moves.
			 *
			 * @param [in,out]	source	The moved mouse.
			 * @param	e			  	Additional event arguments.
			 */
			OPENLIMA_DLL virtual void onMouseMove(openlima::input::Mouse& source,
				const openlima::input::MouseMoveEvent& e);

			/**
			 * Will be called when any mouse button gets pressed/released.
			 *
			 * @param [in,out]	source	The affected mouse.
			 * @param	e			  	Additional event arguments.
			 */
			OPENLIMA_DLL virtual void onMouseClick(openlima::input::Mouse& source,
				const openlima::input::MouseClickEvent& e);

			/**
			 * Will be called when any keyboard button gets pressed.
			 *
			 * @param [in,out]	source	The affected keyboard.
			 * @param	e			  	Additional event arguments.
			 */
			OPENLIMA_DLL virtual void onKeyboardButtonPressed(openlima::input::Keyboard& source,
				const openlima::input::KeyboardEvent& e);

			/**
			 * Will be called when any keyboard button gets released.
			 *
			 * @param [in,out]	source	The affected keyboard.
			 * @param	e			  	Additional event arguments.
			 */
			OPENLIMA_DLL virtual void onKeyboardButtonReleased(openlima::input::Keyboard& source,
				const openlima::input::KeyboardEvent& e);

			/**
			 * Updates this window.
			 *
			 * @param	delta	The elapsed time since the last update.
			 */
			OPENLIMA_DLL virtual void update(openlima::util::dtime delta);

			/**
			 * Renders this window.
			 *
			 * @param	delta	The elapsed time since the last draw.
			 */
			OPENLIMA_DLL virtual void render(openlima::util::dtime delta);

		};

	}
}

#endif /* OPENLIMA_GUI_WINDOW_HPP */
