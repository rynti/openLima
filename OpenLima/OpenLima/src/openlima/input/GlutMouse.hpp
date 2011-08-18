// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_GLUTMOUSE_HPP
#define OPENLIMA_INPUT_GLUTMOUSE_HPP

#include <map>

#include "../util/types.hpp"
#include "Mouse.hpp"


namespace openlima {
	namespace input {

		/**
		 * A GLUT-mouse that is registered for a specific window.
		 *
		 * @sa	Mouse
		 */
		class GlutMouse : public Mouse {
		private:

			/* The registered mouses. */
			static std::map<openlima::util::GlutHandle, GlutMouse*> registeredMouses;

			/* Identifier for the glut window. */
			openlima::util::GlutHandle glutWindowId;


			/**
			 * The global mouse move handler.
			 *
			 * @author	Robert Böhm (rynti)
			 *
			 * @param	x	The x coordinate of the mouse.
			 * @param	y	The y coordinate of the mouse.
			 */
			OPENLIMA_DLL static void globalMouseMove(int x, int y);

			/**
			 * The global mouse click handler.
			 *
			 * @author	Robert Böhm (rynti)
			 *
			 * @param	button	The affected button.
			 * @param	state 	The state of the affected button.
			 * @param	x	  	The x coordinate of the mouse.
			 * @param	y	  	The y coordinate of the mouse.
			 */
			OPENLIMA_DLL static void globalMouseClick(int button, int state, int x, int y);

		protected:

			/**
			 * The mouse move handler.
			 *
			 * @param	x	The x coordinate of the mouse.
			 * @param	y	The y coordinate of the mouse.
			 */
			OPENLIMA_DLL void mouseMove(int x, int y);

			/**
			 * The mouse click handler.
			 *
			 * @param	button	The affected button.
			 * @param	state 	The state of the affected button.
			 * @param	x	  	The x coordinate of the mouse.
			 * @param	y	  	The y coordinate of the mouse.
			 */
			OPENLIMA_DLL void mouseClick(int button, int state, int x, int y);

		public:

			/**
			 * Initializes the mouse and registers the events to it.
			 *
			 * @author	Robert Böhm (rynti)
			 */
			OPENLIMA_DLL GlutMouse(openlima::util::GlutHandle glutWindowId);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~GlutMouse();

			/**
			 * Sets the position of this mouse.
			 *
			 * @param	position	The position, relative to the window of this mouse.
			 */
			OPENLIMA_DLL virtual void setPosition(openlima::util::Vector2i position);

			/**
			 * Sets the visibility of this mouse.
			 *
			 * @param	visible	The visiblity. True if it's visible, false if not.
			 */
			OPENLIMA_DLL virtual void setVisible(bool visible);

		};

	}
}

#endif /* OPENLIMA_INPUT_GLUTMOUSE_HPP */
