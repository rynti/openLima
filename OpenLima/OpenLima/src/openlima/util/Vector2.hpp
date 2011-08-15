// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_VECTOR2_HPP
#define OPENLIMA_UTIL_VECTOR2_HPP


namespace openlima {
	namespace util {

		template <typename T>
		class Vector2 {
		public:
			T x, y;


			Vector2(T x, T y) : x(x), y(y) {}

			Vector2(const Vector2<T>& obj) : x(obj.x), y(obj.y) {}

			Vector2() : x(), y() {}

		};


		typedef Vector2<int> Vector2i;

		typedef Vector2<float> Vector2f;

	}
}


#endif /* OPENLIMA_UTIL_VECTOR2_HPP */