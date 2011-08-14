#include "MouseClickEvent.hpp"

using namespace openlima::util;


namespace openlima {
	namespace input {

		MouseClickEvent::MouseClickEvent(Vector2i position, MouseButton button, MouseButtonState state) {
			this->position = position;
			this->button = button;
			this->state = state;
		}

		Vector2i MouseClickEvent::getPosition() const {
			return this->position;
		}

		MouseButton MouseClickEvent::getButton() const {
			return this->button;
		}

		MouseButtonState MouseClickEvent::getState() const {
			return this->state;
		}

	}
}