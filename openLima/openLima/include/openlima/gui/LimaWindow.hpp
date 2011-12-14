// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GUI_WINDOW_HPP
#define OPENLIMA_GUI_WINDOW_HPP

#include <boost/date_time.hpp>

#include <map>

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/sil/SystemWindow.hpp>
#include <openlima/input/Mouse.hpp>
#include <openlima/input/MouseMoveEvent.hpp>
#include <openlima/input/Keyboard.hpp>
#include <openlima/input/KeyboardEvent.hpp>


namespace openlima {
	namespace gui {

		/**
		 * A window, that can be rendered and uses functionality of openlima::input to provide easy
		 * use of input devices. Also provides methods like render or update, with built-in time
		 * management and render/update limit.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class LimaWindow : public openlima::sil::SystemWindow {
		private:

			/** The default update time. */
			static const openlima::util::dtime defaultUpdateTime;


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
			 *
			 * @param	title	   	The title of the window.
			 * @param	width	   	The width of the window.
			 * @param	height	   	The height of the window.
			 */
			OPENLIMA_DLL LimaWindow(const char* title, int width, int height);


			/**
			 * The resize handler.
			 *
			 * @param	window	The system window where this event came from.
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
			OPENLIMA_DLL virtual ~LimaWindow();


			/**
			 * Hides the console. (If there is one)
			 */
			OPENLIMA_DLL static void hideConsole();


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
			OPENLIMA_DLL openlima::input::Keyboard* getKeyboard();

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
