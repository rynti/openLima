// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_SYSTEMKEYBOARD_HPP
#define OPENLIMA_INPUT_SYSTEMKEYBOARD_HPP

#include <map>

#include "../sil/SystemWindow.hpp"
#include "../util/macros.hpp"
#include "KeyboardButton.hpp"
#include "Keyboard.hpp"


namespace openlima {
	namespace input {

		/**
		 * A system-independent keyboard that is registered for a specific window.
		 *
		 * @sa	Keyboard
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class SystemKeyboard : public Keyboard {
		private:

			/** The window this keyboard is registered on. */
			openlima::sil::SystemWindow& window;

		protected:

			/**
			 * The key-pressed handler.
			 *
			 * @param [in,out]	systemWindow	The window where this event comes from.
			 * @param	key						The pressed key.
			 */
			OPENLIMA_DLL void keyDown(
				openlima::sil::SystemWindow& systemWindow, KeyboardButton key);

			/**
			 * The key-released handler.
			 *
			 * @param [in,out]	systemWindow	The window where this event comes from.
			 * @param	key						The released key.
			 */
			OPENLIMA_DLL void keyUp(
				openlima::sil::SystemWindow& systemWindow, KeyboardButton key);

		public:
			
			/**
			 * Initializes the keyboard and registers the events to it.
			 *
			 * @param	systemWindow	The window this mouse will be registered on.
			 */
			OPENLIMA_DLL SystemKeyboard(openlima::sil::SystemWindow& systemWindow);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~SystemKeyboard();

		};

	}
}

#endif /* OPENLIMA_INPUT_SYSTEMKEYBOARD_HPP */
