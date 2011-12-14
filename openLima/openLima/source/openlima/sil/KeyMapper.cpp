// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <iostream>

#include <openlima/util/macros.hpp>
#include <openlima/input/KeyboardButton.hpp>
#include <openlima/sil/KeyMapper.hpp>

#ifdef OPENLIMA_SIL_XLIB
#include <X11/Xlib.h>
#endif

using namespace openlima::input;


namespace openlima {
	namespace sil {

#ifdef OPENLIMA_SIL_WINAPI
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
			return KeyboardButtonType::KEY_NONE;
		}

#endif

#ifdef OPENLIMA_SIL_XLIB
		KeyboardButton KeyMapper::mapKeycode(Display* display, unsigned int kc) {
			KeySym ks = XKeycodeToKeysym(display, kc, 0);

			if(ks >= 'a' && ks <= 'z') {
				// A - Z
				return (KeyboardButton)(ks - 'a' + 'A');
			}

			if(ks >= '0' && ks <= '9') {
				// 0 - 9
				return (KeyboardButton)(ks);
			}

			switch(ks) {
			case 65470:	return KeyboardButtonType::KEY_F1;
			case 65471:	return KeyboardButtonType::KEY_F2;
			case 65472:	return KeyboardButtonType::KEY_F3;
			case 65473:	return KeyboardButtonType::KEY_F4;
			case 65474:	return KeyboardButtonType::KEY_F5;
			case 65475:	return KeyboardButtonType::KEY_F6;
			case 65476:	return KeyboardButtonType::KEY_F7;
			case 65477:	return KeyboardButtonType::KEY_F8;
			case 65478:	return KeyboardButtonType::KEY_F9;
			case 65479:	return KeyboardButtonType::KEY_F10;
			case 65480:	return KeyboardButtonType::KEY_F11;
			case 65481:	return KeyboardButtonType::KEY_F12;

			case 65361:	return KeyboardButtonType::KEY_LEFT;
			case 65362:	return KeyboardButtonType::KEY_UP;
			case 65363:	return KeyboardButtonType::KEY_RIGHT;
			case 65364:	return KeyboardButtonType::KEY_DOWN;

			case 65365:	return KeyboardButtonType::KEY_PAGE_UP;
			case 65366:	return KeyboardButtonType::KEY_PAGE_DOWN;
			case 65360:	return KeyboardButtonType::KEY_HOME;
			case 65367:	return KeyboardButtonType::KEY_END;
			case 65379:	return KeyboardButtonType::KEY_INSERT;
			case 65407:	return KeyboardButtonType::KEY_NUM_LOCK;
			case 65535:	return KeyboardButtonType::KEY_DELETE;

			case 65507:
			case 65508:	return KeyboardButtonType::KEY_CONTROL;
			case 65513:
			case 65027:	return KeyboardButtonType::KEY_ALT;
			case 65505:
			case 65506:	return KeyboardButtonType::KEY_SHIFT;

			case 65288:	return KeyboardButtonType::KEY_BACK;
			case 65289:	return KeyboardButtonType::KEY_TAB;
			case 65421:
			case 65293:	return KeyboardButtonType::KEY_ENTER;
			case 65299:	return KeyboardButtonType::KEY_PAUSE;
			case 65509:	return KeyboardButtonType::KEY_CAPSLOCK;
			case 65307:	return KeyboardButtonType::KEY_ESCAPE;
			case 32:	return KeyboardButtonType::KEY_SPACE;
			case 65438:	return KeyboardButtonType::KEY_NUMPAD0;
			case 65436:	return KeyboardButtonType::KEY_NUMPAD1;
			case 65433:	return KeyboardButtonType::KEY_NUMPAD2;
			case 65435:	return KeyboardButtonType::KEY_NUMPAD3;
			case 65430:	return KeyboardButtonType::KEY_NUMPAD4;
			case 65437:	return KeyboardButtonType::KEY_NUMPAD5;
			case 65432:	return KeyboardButtonType::KEY_NUMPAD6;
			case 65429:	return KeyboardButtonType::KEY_NUMPAD7;
			case 65431:	return KeyboardButtonType::KEY_NUMPAD8;
			case 65434:	return KeyboardButtonType::KEY_NUMPAD9;
			case 65450:	return KeyboardButtonType::KEY_MULTIPLY;
			case 65451:	return KeyboardButtonType::KEY_ADD;
			case 65453:	return KeyboardButtonType::KEY_SUBTRACT;
			case 65439:	return KeyboardButtonType::KEY_DECIMAL;
			case 65455:	return KeyboardButtonType::KEY_DIVIDE;
			}

			// Missing: OEM-Keys

			return KeyboardButtonType::KEY_NONE;
		}
#endif

		char KeyMapper::getKeyboardButtonValue(KeyboardButton key) {
			if(key >= 'A' && key <= 'Z')
				return (char)key;

			if(key >= '0' && key <= '9')
				return (char)key;

			return 0;
		}

		const char* KeyMapper::getKeyboardButtonDescription(KeyboardButton key) {
			switch(key) {
				case KeyboardButtonType::KEY_NONE:			return "None";

				case KeyboardButtonType::KEY_A:				return "A";
				case KeyboardButtonType::KEY_B:				return "B";
				case KeyboardButtonType::KEY_C:				return "C";
				case KeyboardButtonType::KEY_D:				return "D";
				case KeyboardButtonType::KEY_E:				return "E";
				case KeyboardButtonType::KEY_F:				return "F";
				case KeyboardButtonType::KEY_G:				return "G";
				case KeyboardButtonType::KEY_H:				return "H";
				case KeyboardButtonType::KEY_I:				return "I";
				case KeyboardButtonType::KEY_J:				return "J";
				case KeyboardButtonType::KEY_K:				return "K";
				case KeyboardButtonType::KEY_L:				return "L";
				case KeyboardButtonType::KEY_M:				return "M";
				case KeyboardButtonType::KEY_N:				return "N";
				case KeyboardButtonType::KEY_O:				return "O";
				case KeyboardButtonType::KEY_P:				return "P";
				case KeyboardButtonType::KEY_Q:				return "Q";
				case KeyboardButtonType::KEY_R:				return "R";
				case KeyboardButtonType::KEY_S:				return "S";
				case KeyboardButtonType::KEY_T:				return "T";
				case KeyboardButtonType::KEY_U:				return "U";
				case KeyboardButtonType::KEY_V:				return "V";
				case KeyboardButtonType::KEY_W:				return "W";
				case KeyboardButtonType::KEY_X:				return "X";
				case KeyboardButtonType::KEY_Y:				return "Y";
				case KeyboardButtonType::KEY_Z:				return "Z";

				case KeyboardButtonType::KEY_0:				return "0";
				case KeyboardButtonType::KEY_1:				return "1";
				case KeyboardButtonType::KEY_2:				return "2";
				case KeyboardButtonType::KEY_3:				return "3";
				case KeyboardButtonType::KEY_4:				return "4";
				case KeyboardButtonType::KEY_5:				return "5";
				case KeyboardButtonType::KEY_6:				return "6";
				case KeyboardButtonType::KEY_7:				return "7";
				case KeyboardButtonType::KEY_8:				return "8";
				case KeyboardButtonType::KEY_9:				return "9";

				case KeyboardButtonType::KEY_F1:			return "F1";
				case KeyboardButtonType::KEY_F2:			return "F2";
				case KeyboardButtonType::KEY_F3:			return "F3";
				case KeyboardButtonType::KEY_F4:			return "F4";
				case KeyboardButtonType::KEY_F5:			return "F5";
				case KeyboardButtonType::KEY_F6:			return "F6";
				case KeyboardButtonType::KEY_F7:			return "F7";
				case KeyboardButtonType::KEY_F8:			return "F8";
				case KeyboardButtonType::KEY_F9:			return "F9";
				case KeyboardButtonType::KEY_F10:			return "F10";
				case KeyboardButtonType::KEY_F11:			return "F11";
				case KeyboardButtonType::KEY_F12:			return "F12";

				case KeyboardButtonType::KEY_LEFT:			return "Left";
				case KeyboardButtonType::KEY_UP:			return "Up";
				case KeyboardButtonType::KEY_RIGHT:			return "Right";
				case KeyboardButtonType::KEY_DOWN:			return "Down";
				case KeyboardButtonType::KEY_PAGE_UP:		return "Page Up";
				case KeyboardButtonType::KEY_PAGE_DOWN:		return "Page Down";
				case KeyboardButtonType::KEY_HOME:			return "Home";
				case KeyboardButtonType::KEY_END:			return "End";
				case KeyboardButtonType::KEY_INSERT:		return "Insert";
				case KeyboardButtonType::KEY_NUM_LOCK:		return "Numlock";
				case KeyboardButtonType::KEY_DELETE:		return "Delete";

				case KeyboardButtonType::KEY_CONTROL:		return "Control";
				case KeyboardButtonType::KEY_ALT:			return "Alt";
				case KeyboardButtonType::KEY_SHIFT:			return "Shift";

				case KeyboardButtonType::KEY_BACK:			return "Back";
				case KeyboardButtonType::KEY_TAB:			return "Tab";
				case KeyboardButtonType::KEY_ENTER:			return "Enter";
				case KeyboardButtonType::KEY_PAUSE:			return "Pause";
				case KeyboardButtonType::KEY_CAPSLOCK:		return "Capslock";
				case KeyboardButtonType::KEY_ESCAPE:		return "Escape";
				case KeyboardButtonType::KEY_SPACE:			return "Space";
				case KeyboardButtonType::KEY_NUMPAD0:		return "0 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD1:		return "1 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD2:		return "2 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD3:		return "3 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD4:		return "4 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD5:		return "5 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD6:		return "6 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD7:		return "7 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD8:		return "8 (Numpad)";
				case KeyboardButtonType::KEY_NUMPAD9:		return "9 (Numpad)";
				case KeyboardButtonType::KEY_MULTIPLY:		return "Multiply (Numpad)";
				case KeyboardButtonType::KEY_ADD:			return "Add (Numpad)";
				case KeyboardButtonType::KEY_SUBTRACT:		return "Subtract (Numpad)";
				case KeyboardButtonType::KEY_DECIMAL:		return "Decimal (Numpad)";
				case KeyboardButtonType::KEY_DIVIDE:		return "Divide (Numpad)";
				case KeyboardButtonType::KEY_OEM_PLUS:		return "Plus";
				case KeyboardButtonType::KEY_OEM_COMMA:		return "Comma";
				case KeyboardButtonType::KEY_OEM_MINUS:		return "Minus";
				case KeyboardButtonType::KEY_OEM_PERIOD:	return "Period";
				case KeyboardButtonType::KEY_OEM_1:			return "Special key 1";
				case KeyboardButtonType::KEY_OEM_2:			return "Special key 2";
				case KeyboardButtonType::KEY_OEM_3:			return "Special key 3";
				case KeyboardButtonType::KEY_OEM_4:			return "Special key 4";
				case KeyboardButtonType::KEY_OEM_5:			return "Special key 5";
				case KeyboardButtonType::KEY_OEM_6:			return "Special key 6";
				case KeyboardButtonType::KEY_OEM_7:			return "Special key 7";
				case KeyboardButtonType::KEY_OEM_8:			return "Special key 8";
			}
			return "Unknown";
		}

		const char* KeyMapper::getKeyboardButtonTypeName(KeyboardButton key) {
			switch(key) {
				case KeyboardButtonType::KEY_NONE:			return "KEY_NONE";

				case KeyboardButtonType::KEY_A:				return "KEY_A";
				case KeyboardButtonType::KEY_B:				return "KEY_B";
				case KeyboardButtonType::KEY_C:				return "KEY_C";
				case KeyboardButtonType::KEY_D:				return "KEY_D";
				case KeyboardButtonType::KEY_E:				return "KEY_E";
				case KeyboardButtonType::KEY_F:				return "KEY_F";
				case KeyboardButtonType::KEY_G:				return "KEY_G";
				case KeyboardButtonType::KEY_H:				return "KEY_H";
				case KeyboardButtonType::KEY_I:				return "KEY_I";
				case KeyboardButtonType::KEY_J:				return "KEY_J";
				case KeyboardButtonType::KEY_K:				return "KEY_K";
				case KeyboardButtonType::KEY_L:				return "KEY_L";
				case KeyboardButtonType::KEY_M:				return "KEY_M";
				case KeyboardButtonType::KEY_N:				return "KEY_N";
				case KeyboardButtonType::KEY_O:				return "KEY_O";
				case KeyboardButtonType::KEY_P:				return "KEY_P";
				case KeyboardButtonType::KEY_Q:				return "KEY_Q";
				case KeyboardButtonType::KEY_R:				return "KEY_R";
				case KeyboardButtonType::KEY_S:				return "KEY_S";
				case KeyboardButtonType::KEY_T:				return "KEY_T";
				case KeyboardButtonType::KEY_U:				return "KEY_U";
				case KeyboardButtonType::KEY_V:				return "KEY_V";
				case KeyboardButtonType::KEY_W:				return "KEY_W";
				case KeyboardButtonType::KEY_X:				return "KEY_X";
				case KeyboardButtonType::KEY_Y:				return "KEY_Y";
				case KeyboardButtonType::KEY_Z:				return "KEY_Z";

				case KeyboardButtonType::KEY_0:				return "KEY_0";
				case KeyboardButtonType::KEY_1:				return "KEY_1";
				case KeyboardButtonType::KEY_2:				return "KEY_2";
				case KeyboardButtonType::KEY_3:				return "KEY_3";
				case KeyboardButtonType::KEY_4:				return "KEY_4";
				case KeyboardButtonType::KEY_5:				return "KEY_5";
				case KeyboardButtonType::KEY_6:				return "KEY_6";
				case KeyboardButtonType::KEY_7:				return "KEY_7";
				case KeyboardButtonType::KEY_8:				return "KEY_8";
				case KeyboardButtonType::KEY_9:				return "KEY_9";

				case KeyboardButtonType::KEY_F1:			return "KEY_F1";
				case KeyboardButtonType::KEY_F2:			return "KEY_F2";
				case KeyboardButtonType::KEY_F3:			return "KEY_F3";
				case KeyboardButtonType::KEY_F4:			return "KEY_F4";
				case KeyboardButtonType::KEY_F5:			return "KEY_F5";
				case KeyboardButtonType::KEY_F6:			return "KEY_F6";
				case KeyboardButtonType::KEY_F7:			return "KEY_F7";
				case KeyboardButtonType::KEY_F8:			return "KEY_F8";
				case KeyboardButtonType::KEY_F9:			return "KEY_F9";
				case KeyboardButtonType::KEY_F10:			return "KEY_F10";
				case KeyboardButtonType::KEY_F11:			return "KEY_F11";
				case KeyboardButtonType::KEY_F12:			return "KEY_F12";

				case KeyboardButtonType::KEY_LEFT:			return "KEY_LEFT";
				case KeyboardButtonType::KEY_UP:			return "KEY_UP";
				case KeyboardButtonType::KEY_RIGHT:			return "KEY_RIGHT";
				case KeyboardButtonType::KEY_DOWN:			return "KEY_DOWN";
				case KeyboardButtonType::KEY_PAGE_UP:		return "KEY_PAGE_UP";
				case KeyboardButtonType::KEY_PAGE_DOWN:		return "KEY_PAGE_DOWN";
				case KeyboardButtonType::KEY_HOME:			return "KEY_HOME";
				case KeyboardButtonType::KEY_END:			return "KEY_END";
				case KeyboardButtonType::KEY_INSERT:		return "KEY_INSERT";
				case KeyboardButtonType::KEY_NUM_LOCK:		return "KEY_NUM_LOCK";
				case KeyboardButtonType::KEY_DELETE:		return "KEY_DELETE";

				case KeyboardButtonType::KEY_CONTROL:		return "KEY_CONTROL";
				case KeyboardButtonType::KEY_ALT:			return "KEY_ALT";
				case KeyboardButtonType::KEY_SHIFT:			return "KEY_SHIFT";

				case KeyboardButtonType::KEY_BACK:			return "KEY_BACK";
				case KeyboardButtonType::KEY_TAB:			return "KEY_TAB";
				case KeyboardButtonType::KEY_ENTER:			return "KEY_ENTER";
				case KeyboardButtonType::KEY_PAUSE:			return "KEY_PAUSE";
				case KeyboardButtonType::KEY_CAPSLOCK:		return "KEY_CAPSLOCK";
				case KeyboardButtonType::KEY_ESCAPE:		return "KEY_ESCAPE";
				case KeyboardButtonType::KEY_SPACE:			return "KEY_SPACE";
				case KeyboardButtonType::KEY_NUMPAD0:		return "KEY_NUMPAD0";
				case KeyboardButtonType::KEY_NUMPAD1:		return "KEY_NUMPAD1";
				case KeyboardButtonType::KEY_NUMPAD2:		return "KEY_NUMPAD2";
				case KeyboardButtonType::KEY_NUMPAD3:		return "KEY_NUMPAD3";
				case KeyboardButtonType::KEY_NUMPAD4:		return "KEY_NUMPAD4";
				case KeyboardButtonType::KEY_NUMPAD5:		return "KEY_NUMPAD5";
				case KeyboardButtonType::KEY_NUMPAD6:		return "KEY_NUMPAD6";
				case KeyboardButtonType::KEY_NUMPAD7:		return "KEY_NUMPAD7";
				case KeyboardButtonType::KEY_NUMPAD8:		return "KEY_NUMPAD8";
				case KeyboardButtonType::KEY_NUMPAD9:		return "KEY_NUMPAD9";
				case KeyboardButtonType::KEY_MULTIPLY:		return "KEY_MULTIPLY";
				case KeyboardButtonType::KEY_ADD:			return "KEY_ADD";
				case KeyboardButtonType::KEY_SUBTRACT:		return "KEY_SUBTRACT";
				case KeyboardButtonType::KEY_DECIMAL:		return "KEY_DECIMAL";
				case KeyboardButtonType::KEY_DIVIDE:		return "KEY_DIVIDE";
				case KeyboardButtonType::KEY_OEM_PLUS:		return "KEY_OEM_PLUS";
				case KeyboardButtonType::KEY_OEM_COMMA:		return "KEY_OEM_COMMA";
				case KeyboardButtonType::KEY_OEM_MINUS:		return "KEY_OEM_MINUS";
				case KeyboardButtonType::KEY_OEM_PERIOD:	return "KEY_OEM_PERIOD";
				case KeyboardButtonType::KEY_OEM_1:			return "KEY_OEM_1";
				case KeyboardButtonType::KEY_OEM_2:			return "KEY_OEM_2";
				case KeyboardButtonType::KEY_OEM_3:			return "KEY_OEM_3";
				case KeyboardButtonType::KEY_OEM_4:			return "KEY_OEM_4";
				case KeyboardButtonType::KEY_OEM_5:			return "KEY_OEM_5";
				case KeyboardButtonType::KEY_OEM_6:			return "KEY_OEM_6";
				case KeyboardButtonType::KEY_OEM_7:			return "KEY_OEM_7";
				case KeyboardButtonType::KEY_OEM_8:			return "KEY_OEM_8";
			}

			return "UNKNOWN";
		}


	}
}
