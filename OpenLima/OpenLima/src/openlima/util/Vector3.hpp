#ifndef OPENLIMA_UTIL_VECTOR3_HPP
#define OPENLIMA_UTIL_VECTOR3_HPP


namespace openlima {
	namespace util {

		template <typename T>
		class Vector3 {
		public:
			T x, y, z;

			Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
			Vector3(const Vector3& obj) : x(obj.x), y(obj.y), z(obj.z) {}

		};

	}
}


#endif /* OPENLIMA_UTIL_VECTOR3_HPP */