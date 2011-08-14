#ifndef OPENLIMA_UTIL_VECTOR3I_HPP
#define OPENLIMA_UTIL_VECTOR3I_HPP

#include "Vector3.hpp"


namespace openlima {
	namespace util {

		class Vector3i : public Vector3<int> {
		public:
			Vector3i(int x, int y, int z) : Vector3<int>(x, y, z) {}
			Vector3i() : Vector3<int>(0, 0, 0) {}
		};

	}
}


#endif /* OPENLIMA_UTIL_VECTOR3I_HPP */