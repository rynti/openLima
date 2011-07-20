#ifndef OPENLIMA_UTIL_VECTOR3_HPP
#define OPENLIMA_UTIL_VECTOR3_HPP


namespace openlima {
	namespace util {

		template <typename T>
		class Vector3 {
		public:
			T x, y, z;

			Vector3(T x, T y, T z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}

		};

	}
}


#endif /* OPENLIMA_UTIL_VECTOR3_HPP */