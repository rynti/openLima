// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_SYSTEMMOUSE_HPP
#define OPENLIMA_INPUT_SYSTEMMOUSE_HPP

#include <openlima/util/types.hpp>
#include <openlima/sil/SystemWindow.hpp>
#include <openlima/input/Mouse.hpp>


namespace openlima {
	namespace input {

		/**
		 * A system-independent mouse that is registered for a specific window.
		 *
		 * @sa	Mouse
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class SystemMouse : public Mouse {
		private:

			/** The window this mouse is registered on. */
			openlima::sil::SystemWindow& window;

		protected:

			/**
			 * The mouse move handler.
			 *
			 * @param [in,out]	systemWindow	The window where this event comes from.
			 * @param	x	The x coordinate of the mouse.
			 * @param	y	The y coordinate of the mouse.
			 */
			OPENLIMA_DLL void mouseMove(openlima::sil::SystemWindow& systemWindow, int x, int y);

			/**
			 * The mouse click handler.
			 *
			 * @param [in,out]	systemWindow	The window where this event comes from.
			 * @param	button		  	The affected button.
			 * @param	state		  	The state of the affected button.
			 */
			OPENLIMA_DLL void mouseClick(openlima::sil::SystemWindow& systemWindow,
				MouseButton button, bool state);

		public:

			/**
			 * Initializes the mouse and registers the events to it.
			 *
			 * @param	systemWindow	The window this mouse will be registered on.
			 */
			OPENLIMA_DLL SystemMouse(openlima::sil::SystemWindow& systemWindow);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~SystemMouse();

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

#endif /* OPENLIMA_INPUT_SYSTEMMOUSE_HPP */
