#ifndef OPENLIMA_INPUT_GLOBALMOUSE_HPP
#define OPENLIMA_INPUT_GLOBALMOUSE_HPP

#include "Mouse.hpp"


namespace openlima {
	namespace input {

		class GlobalMouse : public Mouse {
		private:

			/**
			 * Initializes the mouse and registers the global events to it.
			 *
			 * @author	Robert Böhm (rynti)
			 */
			GlobalMouse();


			/**
			 * The event that will be called when the global mouse was moved.
			 *
			 * @author	Robert Böhm (rynti)
			 *
			 * @param	x	The x coordinate of the mouse.
			 * @param	y	The y coordinate of the mouse.
			 */
			static void globalMouseMove(int x, int y);

			/**
			 * The event that will be called when the global mouse was clicked.
			 *
			 * @author	Robert Böhm (rynti)
			 */
			static void globalMouseClick(int button, int state, int x, int y);

		public:

			/**
			 * Returns the global mouse.
			 *
			 * @author	Robert Böhm (rynti)
			 *
			 * @return	The global mouse.
			 */
			OPENLIMA_DLL static GlobalMouse& getInstance();

			/**
			 * Sets the position of this mouse.
			 *
			 * @param	position	The position, relative to the window.
			 */
			OPENLIMA_DLL void setPosition(openlima::util::Vector2i position);

		};

	}
}

#endif /* OPENLIMA_INPUT_GLOBALMOUSE_HPP */