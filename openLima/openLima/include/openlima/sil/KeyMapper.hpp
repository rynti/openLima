// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_SIL_KEYMAPPER_HPP
#define OPENLIMA_SIL_KEYMAPPER_HPP

#include <openlima/util/macros.hpp>
#include <openlima/input/KeyboardButton.hpp>

#ifdef OPENLIMA_SIL_XLIB
#include <X11/Xlib.h>
#endif


namespace openlima {
	namespace sil {

		/**
		 * A key mapper that can map keys of one format to another.
		 */
		class KeyMapper {
		public:

#ifdef OPENLIMA_SIL_WINAPI
		OPENLIMA_DLL static openlima::input::KeyboardButton mapVirtualKey(unsigned int vk);
#endif

#ifdef OPENLIMA_SIL_XLIB
		OPENLIMA_DLL static openlima::input::KeyboardButton mapKeycode(Display* display, unsigned int kc);
#endif
		
		/**
		 * Returns the ASCII character associated with the given key.
		 *
		 * @param key	The keyboard button which should be translated into an ASCII character.
		 *
		 * @return	Either 0x00 if the given key doesn't have a corresponding ASCII character, or
		 *			the corresponding ASCII character.
		 */
		OPENLIMA_DLL static char getKeyboardButtonValue(
			openlima::input::KeyboardButton key);
		
		/**
		 * Returns a description for the given key.
		 *
		 * @param key	The keyboard button which should be described.
		 *
		 * @return	A description for the given key.
		 */
		OPENLIMA_DLL static const char* getKeyboardButtonDescription(
			openlima::input::KeyboardButton key);
		
		/**
		 * Returns the type name of the given key as a string.
		 *
		 * @param key	The keyboard button which type name should be returned.
		 *
		 * @return	The type name of the given key.
		 */
		OPENLIMA_DLL static const char* getKeyboardButtonTypeName(
			openlima::input::KeyboardButton key);

		};

	}
}

#endif /* OPENLIMA_SIL_KEYMAPPER_HPP */
