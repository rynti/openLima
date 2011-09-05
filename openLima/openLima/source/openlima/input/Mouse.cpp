// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <iostream>

#include <openlima/input/Mouse.hpp>

using namespace openlima::util;


namespace openlima {
	namespace input {

		Mouse::Mouse() {
			sticky = false;
			visible = true;
			mouseButtonStates = 0;
		}

		Mouse::Mouse(const Mouse& obj) {
			// Empty
		}

		Mouse::~Mouse() {
			// Empty
		}

		const Vector2i Mouse::getPosition() const {
			return position;
		}

		void Mouse::setPosition(Vector2i position) {
			this->delta = position - this->position;
			this->position = position;
		}

		const Vector2i Mouse::getDelta() const {
			return delta;
		}

		bool Mouse::isSticky() const {
			return this->sticky;
		}

		void Mouse::setSticky(bool sticky) {
			this->sticky = sticky;
		}

		bool Mouse::isVisible() const {
			return this->visible;
		}

		void Mouse::setVisible(bool visible) {
			this->visible = visible;
		}

		bool Mouse::isPressed(MouseButton button) const {
			return (this->mouseButtonStates & (1 << (int)button)) != 0;
		}

	}
}
