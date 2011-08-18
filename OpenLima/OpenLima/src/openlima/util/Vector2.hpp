// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_VECTOR2_HPP
#define OPENLIMA_UTIL_VECTOR2_HPP

#include "types.hpp"


namespace openlima {
	namespace util {

		template <typename T>
		class Vector2 {
		public:
			T x, y;


			Vector2(T x, T y) : x(x), y(y) {}

			Vector2(const Vector2<T>& obj) : x(obj.x), y(obj.y) {}

			Vector2() : x(), y() {}


			bool Vector2::operator ==(const Vector2& other) const {
				return this->x == other.x && this->y == other.y;
			}

			bool Vector2::operator !=(const Vector2& other) const {
				return this->x != other.x || this->y != other.y;
			}


			Vector2 Vector2::operator +(const Vector2& other) const {
				return Vector2(this->x + other.x, this->y + other.y);
			}

			Vector2 Vector2::operator -(const Vector2& other) const {
				return Vector2(this->x - other.x, this->y - other.y);
			}

			Vector2 Vector2::operator *(const Vector2& other) const {
				return Vector2(this->x * other.x, this->y * other.y);
			}

			Vector2 Vector2::operator /(const Vector2& other) const {
				return Vector2(this->x / other.x, this->y / other.y);
			}

		};

		typedef Vector2<i32> Vector2i;

		typedef Vector2<Real> Vector2f;

	}
}

#endif /* OPENLIMA_UTIL_VECTOR2_HPP */
