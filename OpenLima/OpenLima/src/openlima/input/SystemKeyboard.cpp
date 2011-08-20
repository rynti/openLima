// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>

#include <iostream>

#include "SystemKeyboard.hpp"

using namespace openlima::sil;


namespace openlima {
	namespace input {

		SystemKeyboard::SystemKeyboard(SystemWindow& systemWindow) : window(window) {
			systemWindow.onKeyDown = boost::bind(&SystemKeyboard::keyDown, this, _1, _2);
			systemWindow.onKeyUp = boost::bind(&SystemKeyboard::keyUp, this, _1, _2);
		}

		SystemKeyboard::~SystemKeyboard() {
			// Empty
		}


		void SystemKeyboard::keyDown(SystemWindow& systemWindow, KeyboardButton key) {
			this->keyStates[key] = true;
			
			this->onKeyboardButtonPressed(*this, KeyboardEvent((KeyboardButton)key));
		}

		void SystemKeyboard::keyUp(SystemWindow& systemWindow, KeyboardButton key) {
			this->keyStates[key] = false;

			this->onKeyboardButtonReleased(*this, KeyboardEvent((KeyboardButton)key));
		}

	}
}
