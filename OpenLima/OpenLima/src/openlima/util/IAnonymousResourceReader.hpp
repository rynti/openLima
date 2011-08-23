// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_IANONYMOUSRESOURCEREADER_HPP
#define OPENLIMA_UTIL_IANONYMOUSRESOURCEREADER_HPP

#include "macros.hpp"


namespace openlima {
	namespace util {
		
		/**
		 * An anonymous resource reader, which means it doesn't have any type given.
		 * 
		 * Use this only if you know which type the reader you're packing this in has!
		 */
		class IAnonymousResourceReader {
		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~IAnonymousResourceReader() {
				// Empty
			}

		};

	}
}

#endif /* OPENLIMA_UTIL_IANONYMOUSRESOURCEREADER_HPP */