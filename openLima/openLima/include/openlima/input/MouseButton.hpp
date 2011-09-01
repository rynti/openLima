// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSEBUTTON_HPP
#define OPENLIMA_INPUT_MOUSEBUTTON_HPP

#include <openlima/util/macros.hpp>


namespace openlima {
	namespace input {

		/**
		 * A struct that acts like a namespace for all mouse button types.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		struct MouseButtonType {
			/**
			 * Values that represent a mouse button.
			 */
			enum Enum {
				/** The left mouse button. */
				LEFT,
				/** The middle mouse button.  */
				MIDDLE,
				/** The right mouse button.  */
				RIGHT
			};
		};

		/**
		 * Values that represent a mouse button.
		 */
		typedef MouseButtonType::Enum MouseButton;

	}
}

#endif /* OPENLIMA_INPUT_MOUSEBUTTON_HPP */
