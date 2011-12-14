// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/input/MouseMoveEvent.hpp>

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseMoveEvent::MouseMoveEvent(Vector2i position, Vector2i delta)
				: position(position), delta(delta) {
			// Empty
		}

		MouseMoveEvent::~MouseMoveEvent() {
			// Empty
		}

		const Vector2i MouseMoveEvent::getPosition() const {
			return this->position;
		}

		const Vector2i MouseMoveEvent::getDelta() const {
			return this->delta;
		}

	}
}
