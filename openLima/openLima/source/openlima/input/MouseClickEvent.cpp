// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/input/MouseClickEvent.hpp>

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseClickEvent::MouseClickEvent(MouseButton button, bool pressed) {
			this->button = button;
			this->pressed = pressed;
		}

		MouseClickEvent::~MouseClickEvent() {
			// Empty
		}

		MouseButton MouseClickEvent::getButton() const {
			return this->button;
		}

		bool MouseClickEvent::isPressed() const {
			return this->pressed;
		}

	}
}
