// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSE_HPP
#define OPENLIMA_INPUT_MOUSE_HPP

#include <boost/signal.hpp>

#include "../util/macros.hpp"
#include "../util/Vector2.hpp"
#include "MouseButton.hpp"
#include "MouseMoveEvent.hpp"
#include "MouseClickEvent.hpp"


namespace openlima {
	namespace input {

		/**
		 * A abstract mouse. Use specializations like GlutMouse instead.
		 */
		class Mouse {
		private:

			/**
			 * Makes the mouse not copyable.
			 *
			 * @param	obj	The other mouse.
			 */
			Mouse(const Mouse& obj);

		protected:

			/** The position of the mouse. */
			openlima::util::Vector2i position;

			/** The position delta from the last movement. */
			openlima::util::Vector2i delta;

			/** Determines if this mouse is sticked. */
			bool sticky;

			/** Determines if this mouse is visible. */
			bool visible;

			/** 
			 * List of states of the mouse buttons.
			 * 0d = 000b => No button pressed
			 * 1d = 001b => Left button pressed
			 * 2d = 010b => Middle button pressed
			 * 3d = 011b => Left and middle button pressed
			 * 4d = 100b => Right button pressed
			 * ...
			 * 7d = 111b => All buttons pressed
			 */
			int mouseButtonStates;


			/**
			 * Makes this class not instanceable, use specializations instead.
			 */
			OPENLIMA_DLL Mouse();

		public:

			/** An event that will be called when this mouse was moved. */
			boost::signal<void (Mouse&, const MouseMoveEvent&)> onMouseMove;

			/** An event that will be called when this mouse was clicked. */
			boost::signal<void (Mouse&, const MouseClickEvent&)> onMouseClick;


			/**
			 * Returns the current position of this mouse.
			 *
			 * @return	The position of this mouse.
			 */
			OPENLIMA_DLL openlima::util::Vector2i getPosition();

			/**
			 * Sets the position for this mouse.
			 *
			 * @param	position	The new mouse position.
			 */
			OPENLIMA_DLL virtual void setPosition(openlima::util::Vector2i position);

			/**
			 * Returns the delta of this mouse from the last movement.
			 *
			 * @return	The delta of this mouse from the last movement.
			 */
			OPENLIMA_DLL openlima::util::Vector2i getDelta();

			/**
			 * Determines if this mouse is sticky.
			 *
			 * @return	True if the mouse is sticky, false if not.
			 */
			OPENLIMA_DLL bool isSticky();

			/**
			 * Defines if this mouse is sticky. If this mouse is sticky, it will always return to
			 * it's previous position after movements.
			 *
			 * @param	sticky	True to make the mouse "sticky".
			 */
			OPENLIMA_DLL virtual void setSticky(bool sticky);

			/**
			 * Determines if this mouse is visible.
			 *
			 * @return	True if the mouse is visible, false if not.
			 */
			OPENLIMA_DLL bool isVisible();

			/**
			 * Sets the mouse visibility.
			 *
			 * @param	visible	True to make it visible, false to hide.
			 */
			OPENLIMA_DLL virtual void setVisible(bool visible);

			/**
			 * Determines if the given mouse button is currently pressed.
			 *
			 * @param	button	The mouse button.
			 *
			 * @return	True if the given button is currently pressed, false if not.
			 */
			OPENLIMA_DLL bool isPressed(MouseButton button);

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSE_HPP */
