// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_VECTOR2_HPP
#define OPENLIMA_UTIL_VECTOR2_HPP

#include <openlima/util/types.hpp>


namespace openlima {
	namespace util {

		/**
		 * A 2-dimensional vector.
		 */
		template <typename T>
		class Vector2 {
		public:

			/** The x coordinate. */
			T x;

			/** The y coordinate. */
			T y;


			/**
			 * Creates a new 2-dimensional vector based on the given coordinates.
			 *
			 * @param	x	The x coordinate.
			 * @param	y	The y coordinate.
			 */
			Vector2(T x, T y) : x(x), y(y) {}

			/**
			 * Copies the given vector.
			 *
			 * @param	obj	The other vector.
			 */
			Vector2(const Vector2<T>& obj) : x(obj.x), y(obj.y) {}

			/**
			 * Creates a new blank 2-dimensional vector.
			 */
			Vector2() : x(), y() {}


			/**
			 * Compares this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	True if this vector has the same coordinates as the other, else false.
			 */
			bool operator ==(const Vector2& other) const {
				return this->x == other.x && this->y == other.y;
			}

			/**
			 * Compares this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	True if this vector has different coordinates as the other, else false.
			 */
			bool operator !=(const Vector2& other) const {
				return this->x != other.x || this->y != other.y;
			}

			/**
			 * Returns the sum of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The sum of this vector and the other vector.
			 */
			Vector2 operator +(const Vector2& other) const {
				return Vector2(this->x + other.x, this->y + other.y);
			}

			/**
			 * Returns the difference between this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The difference between this vector and the other vector.
			 */
			Vector2 operator -(const Vector2& other) const {
				return Vector2(this->x - other.x, this->y - other.y);
			}

			/**
			 * Returns the product of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The product of this vector and the other vector.
			 */
			Vector2 operator *(const Vector2& other) const {
				return Vector2(this->x * other.x, this->y * other.y);
			}

			/**
			 * Returns the quotient of this vector and the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	The quotient of this vector and the other vector.
			 */
			Vector2 operator /(const Vector2& other) const {
				return Vector2(this->x / other.x, this->y / other.y);
			}

		};

		/**
		 * A 2-dimensional vector of 32-bit integers.
		 */
		typedef Vector2<i32> Vector2i;

		/**
		 * A 2-dimensional vector of floating point numbers.
		 */
		typedef Vector2<Real> Vector2f;

	}
}

#endif /* OPENLIMA_UTIL_VECTOR2_HPP */
