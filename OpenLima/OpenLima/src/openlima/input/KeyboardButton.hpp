// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_KEYBOARDBUTTON_HPP
#define OPENLIMA_INPUT_KEYBOARDBUTTON_HPP


namespace openlima {
	namespace input {

		/**
		 * A struct that acts like a namespace for all keyboard button types.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		struct KeyboardButtonType {
			
			/**
			 * Values that represent a keyboard button.
			 */
			enum Enum {
				KEY_NONE		=	0x0000,

				KEY_A			=	'A',
				KEY_B			=	'B',
				KEY_C			=	'C',
				KEY_D			=	'D',
				KEY_E			=	'E',
				KEY_F			=	'F',
				KEY_G			=	'G',
				KEY_H			=	'H',
				KEY_I			=	'I',
				KEY_J			=	'J',
				KEY_K			=	'K',
				KEY_L			=	'L',
				KEY_M			=	'M',
				KEY_N			=	'N',
				KEY_O			=	'O',
				KEY_P			=	'P',
				KEY_Q			=	'Q',
				KEY_R			=	'R',
				KEY_S			=	'S',
				KEY_T			=	'T',
				KEY_U			=	'U',
				KEY_V			=	'V',
				KEY_W			=	'W',
				KEY_X			=	'X',
				KEY_Y			=	'Y',
				KEY_Z			=	'Z',

				KEY_0			=	'0',
				KEY_1			=	'1',
				KEY_2			=	'2',
				KEY_3			=	'3',
				KEY_4			=	'4',
				KEY_5			=	'5',
				KEY_6			=	'6',
				KEY_7			=	'7',
				KEY_8			=	'8',
				KEY_9			=	'9',

				KEY_F1			=	0x0101,
				KEY_F2			=	0x0102,
				KEY_F3			=	0x0103,
				KEY_F4			=	0x0104,
				KEY_F5			=	0x0105,
				KEY_F6			=	0x0106,
				KEY_F7			=	0x0107,
				KEY_F8			=	0x0108,
				KEY_F9			=	0x0109,
				KEY_F10			=	0x010A,
				KEY_F11			=	0x010B,
				KEY_F12			=	0x010C,

				KEY_LEFT		=	0x0164,
				KEY_UP			=	0x0165,
				KEY_RIGHT		=	0x0166,
				KEY_DOWN		=	0x0167,
				KEY_PAGE_UP		=	0x0168,
				KEY_PAGE_DOWN	=	0x0169,
				KEY_HOME		=	0x016A,
				KEY_END			=	0x016B,
				KEY_INSERT		=	0x016C,
				KEY_NUM_LOCK	=	0x016D,
				KEY_DELETE		=	0x016F,

				KEY_CONTROL		=	0x0170,
				KEY_ALT			=	0x0171,
				KEY_SHIFT		=	0x0172,

				KEY_BACK		=	0x0173,
				KEY_TAB			=	0x0174,
				KEY_ENTER		=	0x0175,
				KEY_PAUSE		=	0x0176,
				KEY_CAPSLOCK	=	0x0177,
				KEY_ESCAPE		=	0x0178,
				KEY_SPACE		=	0x0179,
				KEY_NUMPAD0		=	0x017A,
				KEY_NUMPAD1		=	0x017B,
				KEY_NUMPAD2		=	0x017C,
				KEY_NUMPAD3		=	0x017D,
				KEY_NUMPAD4		=	0x017E,
				KEY_NUMPAD5		=	0x017F,
				KEY_NUMPAD6		=	0x0180,
				KEY_NUMPAD7		=	0x0181,
				KEY_NUMPAD8		=	0x0182,
				KEY_NUMPAD9		=	0x0183,
				KEY_MULTIPLY	=	0x0184,
				KEY_ADD			=	0x0185,
				KEY_SUBTRACT	=	0x0186,
				KEY_DECIMAL		=	0x0187,
				KEY_DIVIDE		=	0x0188,
				KEY_OEM_PLUS	=	0x0189,
				KEY_OEM_COMMA	=	0x018A,
				KEY_OEM_MINUS	=	0x018B,
				KEY_OEM_PERIOD	=	0x018C,
				KEY_OEM_1		=	0x018D,
				KEY_OEM_2		=	0x018E,
				KEY_OEM_3		=	0x018F,
				KEY_OEM_4		=	0x0190,
				KEY_OEM_5		=	0x0191,
				KEY_OEM_6		=	0x0192,
				KEY_OEM_7		=	0x0193,
				KEY_OEM_8		=	0x0194,
			};

		};
		
		/**
		 * Values that represent a keyboard button.
		 */
		typedef KeyboardButtonType::Enum KeyboardButton;

	}
}

#endif /* OPENLIMA_INPUT_KEYBOARDBUTTON_HPP */
