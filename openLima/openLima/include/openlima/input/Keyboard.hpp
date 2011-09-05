// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_KEYBOARD_HPP
#define OPENLIMA_INPUT_KEYBOARD_HPP

#include <boost/signals.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/input/KeyboardButton.hpp>
#include <openlima/input/KeyboardEvent.hpp>


namespace openlima {
	namespace input {

		/**
		 * A abstract keyboard. Use specializations like GlutKeyboard instead.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class Keyboard {
		private:

			static const size_t KEYSTATES_LENGTH = 512;

			/**
			 * Makes the keyboard not copyable.
			 *
			 * @param	obj	The other keyboard.
			 */
			OPENLIMA_DLL Keyboard(const Keyboard& obj);

		protected:

			/** The states of the keys. */
			bool keyStates[KEYSTATES_LENGTH];


			/**
			 * Makes this class not instanceable, use specializations instead.
			 */
			OPENLIMA_DLL Keyboard();

		public:

			/** An event that will be called when any keyboard button was pressed. */
			boost::signal<void (Keyboard&, const KeyboardEvent&)> onKeyboardButtonPressed;

			/** An event that will be called when any keyboard button was released. */
			boost::signal<void (Keyboard&, const KeyboardEvent&)> onKeyboardButtonReleased;


			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Keyboard();


			/**
			 * Query if the given button is pressed.
			 *
			 * @param	button	The button.
			 *
			 * @return	True if the given button is pressed, false if not.
			 */
			OPENLIMA_DLL bool isPressed(KeyboardButton button) const;

		};

	}
}

#endif /* OPENLIMA_INPUT_KEYBOARD_HPP */
