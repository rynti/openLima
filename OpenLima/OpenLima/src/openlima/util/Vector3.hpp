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


			/**
			 * Calculates the surface normal. Use computeNormalized() to normalize the surface normal.
			 *
			 * @param	p1	The first vector of the surface.
			 * @param	p2	The second vector of the surface.
			 * @param	p3	The third vector of the surface.
			 *
			 * @return	The calculated surface normal.
			 */
			static Vector3<T> computeSurfaceNormal(const Vector3<T>& p1, const Vector3<T>& p2,
					const Vector3<T>& p3) {
				Vector3<T> v1 = (p2 - p1);
				Vector3<T> v2 = (p3 - p1);
				Vector3<T> n;
				n.x = (v1.y * v2.z) - (v1.z * v2.y);
				n.y = -((v2.z * v1.x) - (v2.x * v1.z));
				n.z = (v1.x * v2.y) - (v1.y * v2.x);

				return n;
			}


			/**
			 * Gets the normalized version of this vector.
			 *
			 * @return	The normalized version of this vector.
			 */
			Vector3<T> computeNormalized() const {
				T nFactor = sqrt(
					(this->x * this->x) +
					(this->y * this->y) +
					(this->z * this->z));

				return Vector3<T>(
					this->x / nFactor,
					this->y / nFactor,
					this->z / nFactor);
			}

			/**
			 * Compares this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	True if this vector has the same coordinates as the other, else false.
			 */
			bool Vector3::operator ==(const Vector3& other) const {
				return this->x == other.x && this->y == other.y && this->z == other.z;
			}

			/**
			 * Compares this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	True if this vector has different coordinates as the other, else false.
			 */
			bool Vector3::operator !=(const Vector3& other) const {
				return this->x != other.x || this->y != other.y || this->z != other.z;
			}

			/**
			 * Returns the sum of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The sum of this vector and the other vector.
			 */
			Vector3 Vector3::operator +(const Vector3& other) const {
				return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
			}

			/**
			 * Returns the difference between this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The difference between this vector and the other vector.
			 */
			Vector3 Vector3::operator -(const Vector3& other) const {
				return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
			}

			/**
			 * Returns the product of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The product of this vector and the other vector.
			 */
			Vector3 Vector3::operator *(const Vector3& other) const {
				return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
			}

			/**
			 * Returns the quotient of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The quotient of this vector and the other vector.
			 */
			Vector3 Vector3::operator /(const Vector3& other) const {
				return Vector3(this->x / other.x, this->y / other.y, this->z / other.y);
			}

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
