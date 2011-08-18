// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_VECTOR3_HPP
#define OPENLIMA_UTIL_VECTOR3_HPP


namespace openlima {
	namespace util {
		
		/**
		 * A 3-dimensional vector.
		 */
		template <typename T>
		class Vector3 {
		public:

			/** The x coordinate. */
			T x;

			/** The y coordinate. */
			T y;

			/** The z coordinate. */
			T z;


			/**
			 * Creates a new 3-dimensional vector based on the given coordinates.
			 *
			 * @param	x	The x coordinate.
			 * @param	y	The y coordinate.
			 * @param	z	The z coordinate.
			 */
			Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			/**
			 * Copies the given vector.
			 *
			 * @param	obj	The other vector.
			 */
			Vector3(const Vector3<T>& obj) : x(obj.x), y(obj.y), z(obj.z) {}

			/**
			 * Creates a new blank 3-dimensional vector.
			 */
			Vector3() : x(), y(), z() {}

		};

		/**
		 * A 3-dimensional vector of 32-bit integers.
		 */
		typedef Vector3<int> Vector3i;

		/**
		 * A 3-dimensional vector of floating point numbers.
		 */
		typedef Vector3<float> Vector3f;

	}
}

#endif /* OPENLIMA_UTIL_VECTOR3_HPP */
