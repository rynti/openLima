#ifndef OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP
#define OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP

#include "..\util\macros.hpp"
#include "..\util\Vector2i.hpp"


namespace openlima {
	namespace input {

		/**
		 * A event argument that will be given to events that are raised on mouse movements.
		 */
		class MouseMoveEvent {
		private:

			/* The mouse position. */
			openlima::util::Vector2i position;

			/* The mouse position delta. */
			openlima::util::Vector2i delta;

		public:

			/**
			 * Constructor.
			 *
			 * @param	position	The mouse position.
			 */
			L_DLL MouseMoveEvent(openlima::util::Vector2i position, openlima::util::Vector2i delta);


			/**
			 * Returns the mouse position.
			 *
			 * @return	The mouse position.
			 */
			L_DLL openlima::util::Vector2i getPosition();

			/**
			 * Returns the mouse position delta.
			 *
			 * @return	The mouse position delta.
			 */
			L_DLL openlima::util::Vector2i getDelta();

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSEMOVEEVENT_HPP */