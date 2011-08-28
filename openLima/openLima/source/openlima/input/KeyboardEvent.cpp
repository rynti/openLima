// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/input/KeyboardEvent.hpp>
#include <openlima/input/KeyboardButton.hpp>


namespace openlima {
	namespace input {

		KeyboardEvent::KeyboardEvent(KeyboardButton button) {
			this->button = button;
		}

		KeyboardEvent::~KeyboardEvent() {
			// Empty
		}

		KeyboardButton KeyboardEvent::getButton() const {
			return this->button;
		}

	}
}
