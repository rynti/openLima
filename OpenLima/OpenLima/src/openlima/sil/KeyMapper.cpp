// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <iostream>

#include "../util/macros.hpp"
#include "../input/KeyboardButton.hpp"
#include "KeyMapper.hpp"

using namespace openlima::input;


namespace openlima {
	namespace sil {

#ifdef OPENLIMA_WIN
		KeyboardButton KeyMapper::mapVirtualKey(unsigned int vk) {
			if(vk >= 'A' && vk <= 'Z') {
				// Alphanumerical characters
				return (KeyboardButton)(vk);
			}

			if(vk >= '0' && vk <= '9') {
				// Numbers
				return (KeyboardButton)(vk);
			}

			if(vk >= 0x70 && vk <= 0x7B) {
				// Function-keys
				return (KeyboardButton)(vk + 145);
			}
			std::cout << "VKey: " << vk << std::endl;

			// Other keys
			switch(vk) {
			case VK_LEFT:		return KeyboardButtonType::KEY_LEFT;
			case VK_UP:			return KeyboardButtonType::KEY_UP;
			case VK_RIGHT:		return KeyboardButtonType::KEY_RIGHT;
			case VK_DOWN:		return KeyboardButtonType::KEY_DOWN;
			case VK_PRIOR:		return KeyboardButtonType::KEY_PAGE_UP;
			case VK_NEXT:		return KeyboardButtonType::KEY_PAGE_DOWN;
			case VK_HOME:		return KeyboardButtonType::KEY_HOME;
			case VK_END:		return KeyboardButtonType::KEY_END;
			case VK_INSERT:		return KeyboardButtonType::KEY_INSERT;
			case VK_NUMLOCK:	return KeyboardButtonType::KEY_NUM_LOCK;
			case VK_DELETE:		return KeyboardButtonType::KEY_DELETE;

			case VK_BACK:		return KeyboardButtonType::KEY_BACK;
			case VK_TAB:		return KeyboardButtonType::KEY_TAB;
			case VK_RETURN:		return KeyboardButtonType::KEY_ENTER;
			case VK_PAUSE:		return KeyboardButtonType::KEY_PAUSE;
			case VK_CAPITAL:	return KeyboardButtonType::KEY_CAPSLOCK;
			case VK_ESCAPE:		return KeyboardButtonType::KEY_ESCAPE;
			case VK_SPACE:		return KeyboardButtonType::KEY_SPACE;
			case VK_NUMPAD0:	return KeyboardButtonType::KEY_NUMPAD0;
			case VK_NUMPAD1:	return KeyboardButtonType::KEY_NUMPAD1;
			case VK_NUMPAD2:	return KeyboardButtonType::KEY_NUMPAD2;
			case VK_NUMPAD3:	return KeyboardButtonType::KEY_NUMPAD3;
			case VK_NUMPAD4:	return KeyboardButtonType::KEY_NUMPAD4;
			case VK_NUMPAD5:	return KeyboardButtonType::KEY_NUMPAD5;
			case VK_NUMPAD6:	return KeyboardButtonType::KEY_NUMPAD6;
			case VK_NUMPAD7:	return KeyboardButtonType::KEY_NUMPAD7;
			case VK_NUMPAD8:	return KeyboardButtonType::KEY_NUMPAD8;
			case VK_NUMPAD9:	return KeyboardButtonType::KEY_NUMPAD9;
			case VK_MULTIPLY:	return KeyboardButtonType::KEY_MULTIPLY;
			case VK_ADD:		return KeyboardButtonType::KEY_ADD;
			case VK_SUBTRACT:	return KeyboardButtonType::KEY_SUBTRACT;
			case VK_DECIMAL:	return KeyboardButtonType::KEY_DECIMAL;
			case VK_DIVIDE:		return KeyboardButtonType::KEY_DIVIDE;
			case VK_OEM_PLUS:	return KeyboardButtonType::KEY_OEM_PLUS;
			case VK_OEM_COMMA:	return KeyboardButtonType::KEY_OEM_COMMA;
			case VK_OEM_MINUS:	return KeyboardButtonType::KEY_OEM_MINUS;
			case VK_OEM_PERIOD:	return KeyboardButtonType::KEY_OEM_PERIOD;
			case VK_OEM_1:		return KeyboardButtonType::KEY_OEM_1;
			case VK_OEM_2:		return KeyboardButtonType::KEY_OEM_2;
			case VK_OEM_3:		return KeyboardButtonType::KEY_OEM_3;
			case VK_OEM_4:		return KeyboardButtonType::KEY_OEM_4;
			case VK_OEM_5:		return KeyboardButtonType::KEY_OEM_5;
			case VK_OEM_6:		return KeyboardButtonType::KEY_OEM_6;
			case VK_OEM_7:		return KeyboardButtonType::KEY_OEM_7;
			case VK_OEM_8:		return KeyboardButtonType::KEY_OEM_8;

			case VK_LCONTROL:
			case VK_RCONTROL:
			case VK_CONTROL:	return KeyboardButtonType::KEY_CONTROL;

			case VK_LMENU:
			case VK_RMENU:
			case VK_MENU:		return KeyboardButtonType::KEY_ALT;

			case VK_LSHIFT:
			case VK_RSHIFT:
			case VK_SHIFT:		return KeyboardButtonType::KEY_SHIFT;
			}

			// Unknown keys
			std::cout << "Unknown VKey: " << vk << std::endl;
			return KeyboardButtonType::KEY_NONE;
		}

#endif

		char KeyMapper::getKeyboardButtonValue(openlima::input::KeyboardButton key) {
			if(key >= 'A' && key <= 'Z')
				return (char)key;

			if(key >= '0' && key <= '9')
				return (char)key;

			return 0;
		}

		const char* KeyMapper::getKeyboardButtonDescription(openlima::input::KeyboardButton key) {
			char buttonValue = getKeyboardButtonValue(key);

			if(buttonValue != 0) {
				char* retValue = new char[2];
				retValue[0] = buttonValue;
				retValue[1] = 0x00;
				return retValue;
			}

			return NULL;
		}


	}
}
