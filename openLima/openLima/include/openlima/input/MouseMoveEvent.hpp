// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP
#define OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector2.hpp>


namespace openlima {
	namespace input {

		/**
		 * An event argument that will be given to events that are raised on mouse movements.
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class MouseMoveEvent {
		private:

			/** The mouse position. */
			openlima::util::Vector2i position;

			/** The mouse position delta. */
			openlima::util::Vector2i delta;

		public:

			/**
			 * Creates a new MouseMoveEvent argument.
			 *
			 * @param	position	The mouse position.
			 * @param	delta   	The position delta from this movement.
			 */
			OPENLIMA_DLL MouseMoveEvent(openlima::util::Vector2i position,
				openlima::util::Vector2i delta);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~MouseMoveEvent();


			/**
			 * Returns the mouse position.
			 *
			 * @return	The mouse position.
			 */
			OPENLIMA_DLL openlima::util::Vector2i getPosition() const;

			/**
			 * Returns the mouse position delta.
			 *
			 * @return	The mouse position delta.
			 */
			OPENLIMA_DLL openlima::util::Vector2i getDelta() const;

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP */
