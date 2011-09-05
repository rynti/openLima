// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/input/Keyboard.hpp>


namespace openlima {
	namespace input {

		Keyboard::Keyboard(const Keyboard& obj) {
			// Empty
		}
		
		Keyboard::Keyboard() {
			for(size_t i = 0; i < KEYSTATES_LENGTH; i++) {
				this->keyStates[i] = false;
			}
		}

		Keyboard::~Keyboard() {
			// Empty
		}

		bool Keyboard::isPressed(KeyboardButton button) const {
			unsigned int key = (unsigned int)button;
			if(key < KEYSTATES_LENGTH)
				return keyStates[key];

			return false;
		}

	}
}
