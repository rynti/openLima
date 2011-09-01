// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_IRESOURCEREADER_HPP
#define OPENLIMA_UTIL_IRESOURCEREADER_HPP

#include <boost/smart_ptr.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/util/IAnonymousResourceReader.hpp>


namespace openlima {
	namespace util {

		/**
		 * A resource reader for the given resource type T.
		 */
		template <typename T>
		class IResourceReader : public IAnonymousResourceReader {
		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~IResourceReader() {
				// Empty
			}


			/**
			 * Query if 'name' is a legal resource name for this resource reader.
			 *
			 * @param	name	The name of the resource.
			 *
			 * @return	true if the name is legal, false if not.
			 */
			OPENLIMA_DLL virtual bool isLegal(const std::string& name) = 0;

			/**
			 * Reads a resource out of the given input stream.
			 *
			 * @param [in,out]	in	The input stream.
			 *
			 * @return	The read resource.
			 */
			OPENLIMA_DLL virtual boost::shared_ptr<T> readResource(std::istream& in) = 0;

		};

	}
}

#endif /* OPENLIMA_UTIL_IRESOURCEREADER_HPP */
