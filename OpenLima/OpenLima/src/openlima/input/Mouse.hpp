#ifndef OPENLIMA_INPUT_MOUSE_HPP
#define OPENLIMA_INPUT_MOUSE_HPP

#include "..\util\macros.hpp"
#include "..\util\Vector2i.hpp"


namespace openlima {
	namespace input {

		class Mouse {
		private:
			Mouse();

		public:
			static L_DLL Mouse& getInstance();

			L_DLL openlima::util::Vector2i getPosition();
			L_DLL void setPosition(openlima::util::Vector2i position);
			L_DLL void setMouseSticking(bool sticking);
			L_DLL void setMouseVisibility(bool visible);

		};

	}
}

#endif /* OPENLIMA_INPUT_MOUSE_HPP */