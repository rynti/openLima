// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_KEYBOARDEVENT_HPP
#define OPENLIMA_INPUT_KEYBOARDEVENT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/input/KeyboardButton.hpp>


namespace openlima {
	namespace input {

		/**
		 * An event argument that will be given to events that are raised on keyboard button state
		 * changes.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class KeyboardEvent {
		private:

			/** The affected keyboard button. */
			const KeyboardButton button;

		public:

			/**
			 * Creates a new KeyboardEvent argument.
			 *
			 * @param	button  	The affected keyboard button.
			 */
			OPENLIMA_DLL KeyboardEvent(KeyboardButton button);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~KeyboardEvent();


			/**
			 * Returns the affected keyboard button.
			 *
			 * @return	The affected keyboard button.
			 */
			OPENLIMA_DLL const KeyboardButton getButton() const;

		};

	}
}

#endif /* OPENLIMA_INPUT_KEYBOARDEVENT_HPP */
