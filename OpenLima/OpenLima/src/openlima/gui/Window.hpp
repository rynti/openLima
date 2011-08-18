// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GUI_WINDOW_HPP
#define OPENLIMA_GUI_WINDOW_HPP

#include <boost/date_time.hpp>
#include <GL/glut.h>

#include <map>

#include "../util/macros.hpp"
#include "../util/types.hpp"
#include "../input/Mouse.hpp"
#include "../input/MouseMoveEvent.hpp"


namespace openlima {
	namespace gui {

		/**
		 * A window, that can be rendered and uses functionality of openlima::input to provide easy
		 * use of input devices. Also provides methods like render or update, with built-in time
		 * management and render/update limit.
		 * 
		 * Be sure to use Window::initialize(int*, char**) before constructing a Window-object.
		 */
		class Window {
		private:

			/* The default update time. */
			static const openlima::util::dtime defaultUpdateTime;

			/* The registered windows. */
			static std::map<openlima::util::GlutHandle, Window*> registeredWindows;


			/* Identifier for the glut window. */
			openlima::util::GlutHandle glutWindowId;

			/* The time when the previous update happened. */
			boost::posix_time::ptime previousUpdate;

			/* Target time per update. */
			openlima::util::dtime updateTime;

			/* The elapsed time since the last update. */
			openlima::util::dtime updateDelta;

			/* Target time per redraw. */
			openlima::util::dtime redrawTime;

			/* The elapsed time since the last redraw. */
			openlima::util::dtime redrawDelta;

			/**
			 * Determines if redraws are limited.
			 * (If false, redrawTime and redrawDelta are useless)
			 */
			bool limitRedraw;

			/* The mouse for this window. */
			openlima::input::Mouse* mouse;


			/**
			 * The global resize handler.
			 *
			 * @param	width 	The new window width.
			 * @param	height	The new window height.
			 */
			OPENLIMA_DLL static void globalResizeHandler(int width, int height);

			/**
			 * The global draw handler.
			 */
			OPENLIMA_DLL static void globalDrawHandler();

			/**
			 * The global idle handler.
			 */
			OPENLIMA_DLL static void globalIdleHandler();

		protected:

			/**
			 * Creates a new window.
			 * Be sure to call "Window::initialize(int*, char**)" first.
			 *
			 * @param	title	   	The title of the window.
			 * @param	width	   	The width of the window.
			 * @param	height	   	The height of the window.
			 * @param	displayMode	(optional) The display mode of the window.
			 */
			OPENLIMA_DLL Window(const char* title, int width, int height,
				unsigned int displayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


			/**
			 * The resize handler.
			 *
			 * @param	width 	The new window width.
			 * @param	height	The new window height.
			 */
			OPENLIMA_DLL virtual void onResize(int width, int height);

			/**
			 * The draw handler.
			 */
			OPENLIMA_DLL virtual void onDraw();

			/**
			 * The idle handler.
			 */
			OPENLIMA_DLL virtual void onIdle();

		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Window();


			/**
			 * Initializes all the Window-stuff.
			 * Should only be called once per program execution, is required for multiple stuff.
			 *
			 * @param [in,out]	argcp	A pointer to the argument counter.
			 * @param [in,out]	argv 	A pointer to the arguments.
			 */
			OPENLIMA_DLL static void initialize(int* argcp, char** argv);

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
			OPENLIMA_DLL static void setWindowDependency(bool dependent = true);

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
			 * Sets the title of this window.
			 *
			 * @param	title	The title.
			 */
			OPENLIMA_DLL void setTitle(const char* title);

			/**
			 * Sets the size of this window.
			 *
			 * @param	width 	The new window width.
			 * @param	height	The new window height.
			 */
			OPENLIMA_DLL void setSize(int width, int height);

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
