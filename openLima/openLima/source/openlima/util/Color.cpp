// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/Color.hpp>


namespace openlima {
	namespace util {
		
		Color::Color(Real r, Real g, Real b, Real a) : r(r), g(g), b(b), a(a) {
			// Empty
		}

		Color::Color(const Color& obj) : r(obj.r), g(obj.g), b(obj.b), a(obj.a) {
			// Empty
		}

		Color::Color() : r(), g(), b(), a() {
			// Empty
		}

		Color::~Color() {
			// Empty
		}


		u32 Color::getIntRGBA() const {
			return	getIntR() << 24 |
					getIntG() << 16 |
					getIntB() << 8 |
					getIntA();
		}

		u32 Color::getIntARGB() const {
			return	getIntA() << 24 |
					getIntR() << 16 |
					getIntG() << 8 |
					getIntB();
		}

		u8 Color::getIntR() const {
			return static_cast<u8>(this->r * OPENLIMA_REAL(255.0));
		}

		u8 Color::getIntG() const {
			return static_cast<u8>(this->g * OPENLIMA_REAL(255.0));
		}

		u8 Color::getIntB() const {
			return static_cast<u8>(this->b * OPENLIMA_REAL(255.0));
		}

		u8 Color::getIntA() const {
			return static_cast<u8>(this->a * OPENLIMA_REAL(255.0));
		}

		bool Color::operator ==(const Color& other) const {
			return this->r == other.r && this->g == other.g &&
				this->b == other.b && this->a == other.a;
		}

		bool Color::operator !=(const Color& other) const {
			return this->r != other.r || this->g != other.g ||
				this->b != other.b || this->a != other.a;
		}

		Color& Color::operator +=(const Color& other) {
			this->r += other.r;
			this->g += other.g;
			this->b += other.b;
			this->a += other.a;
			return *this;
		}

		Color& Color::operator -=(const Color& other) {
			this->r -= other.r;
			this->g -= other.g;
			this->b -= other.b;
			this->a -= other.a;
			return *this;
		}

		Color& Color::operator *=(const Color& other) {
			this->r *= other.r;
			this->g *= other.g;
			this->b *= other.b;
			this->a *= other.a;
			return *this;
		}

		Color& Color::operator /=(const Color& other) {
			this->r /= other.r;
			this->g /= other.g;
			this->b /= other.b;
			this->a /= other.a;
			return *this;
		}

		Color operator +(const Color& left, const Color& right) {
			Color temp(left);
			temp += right;
			return temp;
		}


		Color operator -(const Color& left, const Color& right) {
			Color temp(left);
			temp -= right;
			return temp;
		}

		Color operator *(const Color& left, const Color& right) {
			Color temp(left);
			temp *= right;
			return temp;
		}
		
		Color operator /(const Color& left, const Color& right) {
			Color temp(left);
			temp /= right;
			return temp;
		}

	}
}
