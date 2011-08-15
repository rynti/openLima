// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include "MouseClickEvent.hpp"

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseClickEvent::MouseClickEvent(Vector2i position, MouseButton button, MouseButtonState state) {
			this->position = position;
			this->button = button;
			this->state = state;
		}

		Vector2i MouseClickEvent::getPosition() const {
			return this->position;
		}

		MouseButton MouseClickEvent::getButton() const {
			return this->button;
		}

		MouseButtonState MouseClickEvent::getState() const {
			return this->state;
		}

	}
}