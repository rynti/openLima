// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/input/MouseClickEvent.hpp>

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseClickEvent::MouseClickEvent(MouseButton button, bool pressed)
				: button(button), pressed(pressed) {
			// Empty
		}

		MouseClickEvent::~MouseClickEvent() {
			// Empty
		}

		const MouseButton MouseClickEvent::getButton() const {
			return this->button;
		}

		bool MouseClickEvent::isPressed() const {
			return this->pressed;
		}

	}
}
