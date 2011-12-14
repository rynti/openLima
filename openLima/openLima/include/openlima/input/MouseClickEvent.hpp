// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSECLICKEVENT_HPP
#define OPENLIMA_INPUT_MOUSECLICKEVENT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector2.hpp>
#include <openlima/input/MouseButton.hpp>


namespace openlima {
	namespace input {

		/**
		 * An event argument that will be given to events that are raised on mouse clicks.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class MouseClickEvent {
		private:

			/** The affected mouse button. */
			const MouseButton button;

			/** Determines if the affected mouse button is currently pressed. */
			const bool pressed;

		public:

			/**
			 * Creates a new MouseClickEvent argument.
			 *
			 * @param	button  	The affected mouse button.
			 * @param	pressed   	Determines if the affected mouse button is currently pressed.
			 */
			OPENLIMA_DLL MouseClickEvent(MouseButton button, bool pressed);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~MouseClickEvent();


			/**
			 * Returns the affected mouse button.
			 *
			 * @return	The affected mouse button.
			 */
			OPENLIMA_DLL const MouseButton getButton() const;

			/**
			 * Determines if the affected mouse button is currently pressed.
			 *
			 * @return	The state of the affected mouse button.
			 */
			OPENLIMA_DLL bool isPressed() const;

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSECLICKEVENT_HPP */
