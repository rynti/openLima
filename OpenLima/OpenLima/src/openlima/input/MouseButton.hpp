#ifndef OPENLIMA_INPUT_MOUSEBUTTON_HPP
#define OPENLIMA_INPUT_MOUSEBUTTON_HPP

#include "../util/macros.hpp"


namespace openlima {
	namespace input {
		
		struct mouse_button {
			enum Enum {
				/* The left mouse button. */
				LEFT,
				/* The middle mouse button.  */
				MIDDLE,
				/* The right mouse button.  */
				RIGHT
			};
		};
		
		/**
		 * Values that represent a mouse button.
		 */
		typedef mouse_button::Enum MouseButton;

	}
}

#endif /* OPENLIMA_INPUT_MOUSEBUTTON_HPP */