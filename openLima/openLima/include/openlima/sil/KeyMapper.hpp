// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_SIL_KEYMAPPER_HPP
#define OPENLIMA_SIL_KEYMAPPER_HPP

#include "../util/macros.hpp"
#include "../input/KeyboardButton.hpp"


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

		OPENLIMA_DLL static char getKeyboardButtonValue(
			openlima::input::KeyboardButton key);

		OPENLIMA_DLL static const char* getKeyboardButtonDescription(
			openlima::input::KeyboardButton key);

		};

	}
}

#endif /* OPENLIMA_SIL_KEYMAPPER_HPP */
