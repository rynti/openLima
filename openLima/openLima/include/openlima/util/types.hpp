// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/cstdint.hpp>

#include <openlima/util/macros.hpp>


namespace openlima {
	namespace util {

		////////////////////////////////
		// Signed numbers

		/** A 8-bit signed number. */
		typedef boost::int8_t i8;

		/** A 16-bit signed number. */
		typedef boost::int16_t i16;

		/** A 32-bit signed number. */
		typedef boost::int32_t i32;

		/** A 64-bit signed number. */
		typedef boost::int64_t i64;


		////////////////////////////////
		// Unsigned numbers

		/** A 8-bit unsigned number. */
		typedef boost::uint8_t u8;

		/** A 16-bit unsigned number. */
		typedef boost::uint16_t u16;

		/** A 32-bit unsigned number. */
		typedef boost::uint32_t u32;

		/** A 64-bit unsigned number. */
		typedef boost::uint64_t u64;


		////////////////////////////////
		// Others

		/** A GLUT-handle, for instance a window. */
		typedef int GlutHandle;

		/** "Delta time" - A time duration. Will always be given in seconds. */
		typedef double dtime;

		/**
		 * A floating point type that can be either float or double, based on the precision given.
		 *
		 * Define OPENLIMA_PRECISE_REAL when compiling openlima to let Real be a double.
		 */
		typedef OPENLIMA_REAL_TYPE Real;

	}
}
