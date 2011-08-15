// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSECLICKEVENT_HPP
#define OPENLIMA_INPUT_MOUSECLICKEVENT_HPP

#include "../util/macros.hpp"
#include "../util/Vector2.hpp"
#include "MouseButton.hpp"
#include "MouseButtonState.hpp"


namespace openlima {
	namespace input {

		/**
		 * A event argument that will be given to events that are raised on mouse clicks.
		 */
		class MouseClickEvent {
		private:

			/* The mouse position. */
			openlima::util::Vector2i position;

			/* The affected mouse button. */
			MouseButton button;

			/* The state of the affected mouse button. */
			MouseButtonState state;

		public:

			/**
			 * Constructor.
			 *
			 * @param	position	The mouse position.
			 * @param	button  	The affected mouse button.
			 * @param	state   	The state of the affected mouse button.
			 */
			OPENLIMA_DLL MouseClickEvent(openlima::util::Vector2i position, MouseButton button, MouseButtonState state);


			/**
			 * Returns the mouse position.
			 *
			 * @return	The mouse position.
			 */
			OPENLIMA_DLL openlima::util::Vector2i getPosition() const;

			/**
			 * Returns the affected mouse button.
			 *
			 * @return	The affected mouse button.
			 */
			OPENLIMA_DLL MouseButton getButton() const;

			/**
			 * Returns the state of the affected mouse button.
			 *
			 * @return	The state of the affected mouse button.
			 */
			OPENLIMA_DLL MouseButtonState getState() const;

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSECLICKEVENT_HPP */