// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

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
			 * Adds the given other vector to this vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	This vector.
			 */
			Vector2<T>& operator +=(const Vector2<T>& other) {
				this->x += other.x;
				this->y += other.y;
				return *this;
			}

			/**
			 * Subtracts this vector by the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	This vector.
			 */
			Vector2<T>& operator -=(const Vector2<T>& other) {
				this->x -= other.x;
				this->y -= other.y;
				return *this;
			}

			/**
			 * Multiplies this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	This vector.
			 */
			Vector2<T>& operator *=(const Vector2<T>& other) {
				this->x *= other.x;
				this->y *= other.y;
				return *this;
			}

			/**
			 * Divides this vector by the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	This vector.
			 */
			Vector2<T>& operator /=(const Vector2<T>& other) {
				this->x /= other.x;
				this->y /= other.y;
				return *this;
			}

		};

		/**
		 * Returns the sum of two vectors.
		 *
		 * @param	left	The first summand.
		 * @param	right	The second summand.
		 *
		 * @return	The sum of the given vectors.
		 */
		template<typename T>
		Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {
			Vector2<T> temp(left);
			temp += right;
			return temp;
		}

		/**
		 * Returns the difference between two vectors.
		 *
		 * @param	left	The minuend.
		 * @param	right	The subtrahend.
		 *
		 * @return	The difference between the given vectors.
		 */
		template<typename T>
		Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {
			Vector2<T> temp(left);
			temp -= right;
			return temp;
		}

		/**
		 * Returns the product of two vectors.
		 *
		 * @param	left	The first factor.
		 * @param	right	The second factor.
		 *
		 * @return	The product of the given vectors.
		 */
		template<typename T>
		Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right) {
			Vector2<T> temp(left);
			temp *= right;
			return temp;
		}
		
		/**
		 * Returns the quotient of two vectors.
		 *
		 * @param	left	The dividend.
		 * @param	right	The divisor.
		 *
		 * @return	The quotient of the given vectors.
		 */
		template<typename T>
		Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right) {
			Vector2<T> temp(left);
			temp /= right;
			return temp;
		}


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
