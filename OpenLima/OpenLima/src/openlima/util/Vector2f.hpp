#ifndef OPENLIMA_UTIL_VECTOR2F_HPP
#define OPENLIMA_UTIL_VECTOR2F_HPP

#include "Vector2.hpp"


namespace openlima {
	namespace util {

		class Vector2f : public Vector2<float> {
		public:
			Vector2f(float x, float y) : Vector2<float>(x, y) {}
			Vector2f() : Vector2<float>(0.0f, 0.0f) {}
		};

	}
}

#endif /* OPENLIMA_UTIL_VECTOR2F_HPP */