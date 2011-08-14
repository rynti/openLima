#ifndef OPENLIMA_UTIL_VECTOR3_HPP
#define OPENLIMA_UTIL_VECTOR3_HPP


namespace openlima {
	namespace util {

		template <typename T>
		class Vector3 {
		public:
			T x, y, z;


			Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			Vector3(const Vector3<T>& obj) : x(obj.x), y(obj.y), z(obj.z) {}

			Vector3() : x(), y(), z() {}

		};


		typedef Vector3<int> Vector3i;

		typedef Vector3<float> Vector3f;

	}
}


#endif /* OPENLIMA_UTIL_VECTOR3_HPP */