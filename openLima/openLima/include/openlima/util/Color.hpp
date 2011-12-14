// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_COLOR_HPP
#define OPENLIMA_UTIL_COLOR_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>


namespace openlima {
	namespace util {

		/**
		 * A color.
		 */
		class Color {
		public:

			/** The red component. */
			Real r;

			/** The green component. */
			Real g;

			/** The blue component. */
			Real b;

			/** The alpha component. */
			Real a;


			/**
			 * Creates a new color based on the given color components. The components' values
			 * should be between 0 and 1.
			 *
			 * @param	r	The red component.
			 * @param	g	The green component.
			 * @param	b	The blue component.
			 * @param	a	The alpha component.
			 */
			OPENLIMA_DLL Color(Real r, Real g, Real b, Real a);

			/**
			 * Copies the given color.
			 *
			 * @param	obj	The other color.
			 */
			OPENLIMA_DLL Color(const Color& obj);

			/**
			 * Creates a new blank color.
			 */
			OPENLIMA_DLL Color();

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Color();


			/**
			 * Returns this color as an integer in the following format: 0xRRGGBBAA.
			 */
			OPENLIMA_DLL u32 getIntRGBA() const;

			/**
			 * Returns this color as an integer in the following format: 0xAARRGGBB.
			 */
			OPENLIMA_DLL u32 getIntARGB() const;

			/**
			 * Returns this color as an integer in the following format: 0xRRGGBB.
			 *
			 * Be aware that this will remove the alpha component.
			 */
			OPENLIMA_DLL u32 getIntGBA() const;
			
			/**
			 * Returns the red component of this color as an integer. It ranges from 0-255, where
			 * 1.0 equals 255 and 0.0 equals 0.
			 */
			OPENLIMA_DLL u8 getIntR() const;
			
			/**
			 * Returns the green component of this color as an integer. It ranges from 0-255, where
			 * 1.0 equals 255 and 0.0 equals 0.
			 */
			OPENLIMA_DLL u8 getIntG() const;
			
			/**
			 * Returns the blue component of this color as an integer. It ranges from 0-255, where
			 * 1.0 equals 255 and 0.0 equals 0.
			 */
			OPENLIMA_DLL u8 getIntB() const;
			
			/**
			 * Returns the alpha component of this color as an integer. It ranges from 0-255, where
			 * 1.0 equals 255 and 0.0 equals 0.
			 */
			OPENLIMA_DLL u8 getIntA() const;

			/**
			 * Compares this color with the given other color.
			 *
			 * @param	other	The other color.
			 *
			 * @return	True if this vector has the same color as the other, else false.
			 */
			OPENLIMA_DLL bool operator ==(const Color& other) const;

			/**
			 * Compares this vector with the given other vector.
			 *
			 * @param	other	The other vector.
			 *
			 * @return	True if this vector has different coordinates as the other, else false.
			 */
			OPENLIMA_DLL bool operator !=(const Color& other) const;

			/**
			 * Adds the given other color to this color.
			 *
			 * @param	other	The other color.
			 *
			 * @return	This color.
			 */
			OPENLIMA_DLL Color& operator +=(const Color& other);

			/**
			 * Subtracts this color by the given other color.
			 *
			 * @param	other	The other color.
			 *
			 * @return	This color.
			 */
			OPENLIMA_DLL Color& operator -=(const Color& other);

			/**
			 * Multiplies this color with the given other color.
			 *
			 * @param	other	The other color.
			 *
			 * @return	This color.
			 */
			OPENLIMA_DLL Color& operator *=(const Color& other);

			/**
			 * Divides this color by the given other color.
			 *
			 * @param	other	The other color.
			 *
			 * @return	This color.
			 */
			OPENLIMA_DLL Color& operator /=(const Color& other);

		};

		/**
		 * Returns the sum of two colors.
		 *
		 * @param	left	The first summand.
		 * @param	right	The second summand.
		 *
		 * @return	The sum of the given colors.
		 */
		OPENLIMA_DLL Color operator +(const Color& left, const Color& right);

		/**
		 * Returns the difference between two colors.
		 *
		 * @param	left	The minuend.
		 * @param	right	The subtrahend.
		 *
		 * @return	The difference between the given colors.
		 */
		OPENLIMA_DLL Color operator -(const Color& left, const Color& right);

		/**
		 * Returns the product of two colors.
		 *
		 * @param	left	The first factor.
		 * @param	right	The second factor.
		 *
		 * @return	The product of the given colors.
		 */
		OPENLIMA_DLL Color operator *(const Color& left, const Color& right);
		
		/**
		 * Returns the quotient of two colors.
		 *
		 * @param	left	The dividend.
		 * @param	right	The divisor.
		 *
		 * @return	The quotient of the given colors.
		 */
		OPENLIMA_DLL Color operator /(const Color& left, const Color& right);

	}
}

#endif /* OPENLIMA_UTIL_COLOR_HPP */
