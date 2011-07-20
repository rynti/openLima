#ifndef OPENLIMA_UTIL_VECTOR2I_HPP
#define OPENLIMA_UTIL_VECTOR2I_HPP

#include "Vector2.hpp"


namespace openlima {
	namespace util {

		class Vector2i : public Vector2<int> {
		public:
			Vector2i(int x, int y) : Vector2<int>(x, y) {}
			Vector2i() : Vector2(0, 0) {}
		};

	}
}


#endif /* OPENLIMA_UTIL_VECTOR2I_HPP */