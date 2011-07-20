#ifndef OPENLIMA_UTIL_VECTOR2_HPP
#define OPENLIMA_UTIL_VECTOR2_HPP


namespace openlima {
	namespace util {

		template <typename T>
		class Vector2 {
		public:
			T x, y;

			Vector2(T x, T y) {
				this->x = x;
				this->y = y;
			}

		};

	}
}


#endif /* OPENLIMA_UTIL_VECTOR2_HPP */