// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP
#define OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP

#include "../util/macros.hpp"


namespace openlima {
	namespace input {

		struct MouseButtonStateType {
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
		typedef MouseButtonStateType::Enum MouseButtonState;

	}
}

#endif /* OPENLIMA_INPUT_MOUSEBUTTONSTATE_HPP */