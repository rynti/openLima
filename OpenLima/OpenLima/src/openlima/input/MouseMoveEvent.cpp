// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include "MouseMoveEvent.hpp"

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseMoveEvent::MouseMoveEvent(Vector2i position, Vector2i delta) {
			this->position = position;
			this->delta = delta;
		}

		Vector2i MouseMoveEvent::getPosition() const {
			return this->position;
		}

		Vector2i MouseMoveEvent::getDelta() const {
			return this->delta;
		}

	}
}