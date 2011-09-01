// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>

#include <openlima/sil/SystemWindow.hpp>
#include <openlima/input/SystemMouse.hpp>

using namespace openlima::util;
using namespace openlima::sil;


namespace openlima {
	namespace input {

		SystemMouse::SystemMouse(SystemWindow& systemWindow) : window(systemWindow) {
			window.mouseMoveFunction = boost::bind(&SystemMouse::mouseMove, this, _1, _2, _3);
			window.mouseClickFunction = boost::bind(&SystemMouse::mouseClick, this, _1, _2, _3);
		}

		SystemMouse::~SystemMouse() {
			// Empty
		}


		void SystemMouse::mouseMove(SystemWindow& systemWindow, int x, int y) {
			if(this->position == Vector2i(x, y))
				return;

			this->delta = Vector2i(x - this->position.x, y - this->position.y);

			this->position = Vector2i(x, y);

			this->onMouseMove(*this, MouseMoveEvent(this->getPosition(), this->getDelta()));

			if(this->sticky && (this->delta.x != 0 || this->delta.y != 0)) {
				//glutSetWindow(this->glutWindowId);
				//int newX = glutGet(GLUT_WINDOW_WIDTH) / 2;
				//int newY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
				this->setPosition(Vector2i(this->window.getWidth() / 2,
					this->window.getHeight() / 2));
			}
		}

		void SystemMouse::mouseClick(SystemWindow& systemWindow, MouseButton button, bool state) {
			if(state) {
				this->mouseButtonStates |= (1 << button);
			} else {
				this->mouseButtonStates &= ~(1 << button);
			}
			this->onMouseClick(*this, MouseClickEvent(button, state));
		}

		void SystemMouse::setPosition(Vector2i position) {
			Mouse::setPosition(position);
			this->window.setMousePosition(position.x, position.y);
			//glutSetWindow(this->glutWindowId);
			//glutWarpPointer(position.x, position.y);
		}

		void SystemMouse::setVisible(bool visible) {
			Mouse::setVisible(visible);

			if(visible) {
				window.setMouseVisibility(visible);
			} else {
				window.setMouseVisibility(visible);
			}
		}

	}
}
