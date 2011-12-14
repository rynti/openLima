// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_FILERESOURCEMANAGER_HPP
#define OPENLIMA_UTIL_FILERESOURCEMANAGER_HPP

#include <boost/smart_ptr.hpp>
#include <boost/filesystem.hpp>

#include <string>
#include <iostream>

#include <openlima/util/ResourceManager.hpp>


namespace openlima {
	namespace util {

		/**
		 * A resource manager based on the file system.
		 *
		 * @sa	ResourceManager
		 */
		class FileResourceManager : public ResourceManager {
		private:

			/** Pathname of the parent directory, from where the resources are getting loaded. */
			const std::string parentDirectory;

		protected:

			/**
			 * Opens a resource stream.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	A stream to the given resource. Will be closed after used.
			 */
			OPENLIMA_DLL virtual boost::shared_ptr<std::istream>
				openResourceStream(const std::string& name) const;

			/**
			 * Closes a resource stream.
			 *
			 * @param	in	The input stream.
			 */
			OPENLIMA_DLL virtual void closeResourceStream(
				boost::shared_ptr<std::istream> in) const;

			/**
			 * Queries if a given resource exists.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	True if the given resource exists, false if not.
			 */
			OPENLIMA_DLL virtual bool resourceExists(const std::string& name) const;

		public:

			/**
			 * Creates a new file resource manager.
			 */
			OPENLIMA_DLL FileResourceManager();

			/**
			 * Creates a new file resource manager.
			 *
			 * @param	parent	The parent directory.
			 */
			OPENLIMA_DLL FileResourceManager(const std::string& parent);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~FileResourceManager();

		};

	}
}

#endif /* OPENLIMA_UTIL_FILERESOURCEMANAGER_HPP */
