#ifndef OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP
#define OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP

#include "../util/macros.hpp"


namespace openlima {
	namespace input {

		struct mouse_button_state {
			enum Enum {
				/* The button is released.  */
				RELEASED,
				/* The button is pressed.  */
				PRESSED
			};
		};
		
		/**
		 * Values that represent the state of a mouse button.
		 */
		typedef mouse_button_state::Enum MouseButtonState;

	}
}

#endif /* OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP */