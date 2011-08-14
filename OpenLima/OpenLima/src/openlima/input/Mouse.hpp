#ifndef OPENLIMA_INPUT_MOUSE_HPP
#define OPENLIMA_INPUT_MOUSE_HPP

#include <boost/signal.hpp>
#include "..\util\macros.hpp"
#include "..\util\Vector2i.hpp"
#include "MouseButton.hpp"
#include "MouseButtonState.hpp"
#include "MouseMoveEvent.hpp"
#include "MouseClickEvent.hpp"


namespace openlima {
	namespace input {

		class Mouse {
		protected:

			/* The position of the mouse. */
			openlima::util::Vector2i position;

			/* The delta movement of the last onMouseMove-event. */
			openlima::util::Vector2i delta;

			/* Determines if this mouse is sticked. */
			bool sticky;

			/* Determines if this mouse is visible. */
			bool visible;

			/** 
			 * List of states of the mouse buttons.
			 * 0d = 000b => No button pressed
			 * 1d = 001b => Left button pressed
			 * 2d = 010b => Middle button pressed
			 * 3d = 011b => Left and middle button pressed
			 * 4d = 100b => Right button pressed
			 * ...
			 * 7d = 111b => All buttons pressed
			 */
			int mouseButtonStates;

			/**
			 * Default constructor.
			 */
			L_DLL Mouse();

		public:

			boost::signal<void (Mouse&, MouseMoveEvent&)> onMouseMove;

			boost::signal<void (Mouse&, MouseClickEvent&)> onMouseClick;

			/**
			 * Returns the current position of this mouse.
			 *
			 * @return	The position of this mouse, relative to the window.
			 */
			L_DLL openlima::util::Vector2i getPosition();

			/**
			 * Returns the delta of this mouse from the last movement.
			 *
			 * @return	The delta of this mouse from the last movement.
			 */
			L_DLL openlima::util::Vector2i getDelta();

			/**
			 * Determines if this mouse is sticky.
			 *
			 * @return	true if it is sticky, false if not.
			 */
			L_DLL bool isSticky();

			/**
			 * Defines if this mouse is sticky. If this mouse is sticky, it will always move back to
			 * the middle of the window.
			 *
			 * @param	sticky	true to make the mouse "sticky".
			 */
			L_DLL void setSticky(bool sticky);

			/**
			 * Determines if this mouse is visible.
			 *
			 * @return	true if it is visible, false if not.
			 */
			L_DLL bool isVisible();

			/**
			 * Sets the mouse visibility.
			 *
			 * @param	visible	true to make it visible, false to hide.
			 */
			L_DLL void setVisible(bool visible);

			/**
			 * Gets the state of the given mouse button.
			 *
			 * @param	button	The mouse button.
			 *
			 * @return	The state of the given mouse button.
			 */
			L_DLL MouseButtonState getButtonState(MouseButton button);

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSE_HPP */