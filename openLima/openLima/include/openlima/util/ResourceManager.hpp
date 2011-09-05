// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_UTIL_RESOURCEMANAGER_HPP
#define OPENLIMA_UTIL_RESOURCEMANAGER_HPP

#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>

#include <map>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <string>

#include <openlima/util/macros.hpp>
#include <openlima/util/IResourceReader.hpp>


namespace openlima {
	namespace util {

		/**
		 * Manager for resources with capabilities of resource caching.
		 *
		 * @sa	FileResourceManager
		 */
		class ResourceManager {
		protected:

			/** The registered readers. */
			std::map<const std::type_info*,
				std::vector<boost::shared_ptr<IAnonymousResourceReader> > > registeredReaders;

			/** The cached resources. */
			std::map<const std::string, boost::weak_ptr<void> > cachedResources;


			/**
			 * Makes this class not instanceable, use specializations like FileResourceManager
			 * instead.
			 */
			OPENLIMA_DLL ResourceManager() {
				// Empty
			}


			/**
			 * Opens a resource stream.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	A stream to the given resource. Will be closed after used.
			 */
			OPENLIMA_DLL virtual boost::shared_ptr<std::istream>
				openResourceStream(const std::string& name) const = 0;

			/**
			 * Closes a resource stream.
			 *
			 * @param	in	The input stream.
			 */
			OPENLIMA_DLL virtual void closeResourceStream(
				boost::shared_ptr<std::istream> in) const = 0;

			/**
			 * Queries if a given resource exists.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	True if the given resource exists, false if not.
			 */
			OPENLIMA_DLL virtual bool resourceExists(const std::string& name) const = 0;

		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~ResourceManager() {
				// Empty
			}

			/**
			 * Registers the given reader.
			 *
			 * @param	reader	The resource reader.
			 */
			template <typename T>
			OPENLIMA_DLL void registerReader(boost::shared_ptr<IResourceReader<T> > reader) {
				this->registeredReaders[&typeid(T)].push_back(reader);
			}

			/**
			 * Registers the given reader.
			 *
			 * @param [in,out]	reader	The resource reader.
			 */
			template <typename T>
			OPENLIMA_DLL void registerReader(IResourceReader<T>* reader) {
				this->registerReader<T>(boost::shared_ptr<IResourceReader<T> >(reader));
			}

			/**
			 * Requests a resource.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	The resource, or a null-pointer if no reader could be found or
			 * 			the resource doesn't exist.
			 */
			template <typename T>
			OPENLIMA_DLL boost::shared_ptr<T>
					getResource(const std::string& name) {

				if(cachedResources.count(name) > 0 && !cachedResources[name].expired()) {
					return boost::static_pointer_cast<T>(cachedResources[name].lock());
				}

				return getRefreshedResource<T>(name);
			}

			/**
			 * Requests a resource.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	The resource, or a null-pointer if no reader could be found or
			 * 			the resource doesn't exist.
			 */
			template <typename ResourceType, typename ReaderType>
			OPENLIMA_DLL boost::shared_ptr<ResourceType>
					getResource(const std::string& name) {

				if(cachedResources.count(name) > 0 && !cachedResources[name].expired()) {
					return boost::static_pointer_cast<ResourceType>(cachedResources[name].lock());
				}

				return getRefreshedResource<ResourceType, ReaderType>(name);
			}

			/**
			 * Requests a refreshed resource, which means that the resource will be loaded, even if
			 * the requested resource is already in the cache.
			 * The correct resource reader is choosen by the resource name and the reader's
			 * isLegal() method.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	The refreshed resource, or a null-pointer if no reader could be found or
			 * 			the resource doesn't exist.
			 */
			template <typename T>
			OPENLIMA_DLL boost::shared_ptr<T>
					getRefreshedResource(const std::string& name) {

				if(!this->resourceExists(name))
					return boost::shared_ptr<T>();

				const std::vector<boost::shared_ptr<IAnonymousResourceReader> >& readerList =
					this->registeredReaders.find(&typeid(T))->second;

				BOOST_FOREACH(boost::shared_ptr<IAnonymousResourceReader> anonymousReader,
						readerList) {
					boost::shared_ptr<IResourceReader<T> > reader =
						boost::dynamic_pointer_cast<IResourceReader<T> >(anonymousReader);

					if(reader->isLegal(name)) {
						boost::shared_ptr<std::istream> istream = this->openResourceStream(name);
						boost::shared_ptr<T> sPtr = reader->readResource(*istream);
						this->closeResourceStream(istream);
						this->cachedResources[name] = sPtr;
						return sPtr;
					}
				}

				return boost::shared_ptr<T>();
			}

			/**
			 * Requests a refreshed resource, which means that the resource will be loaded, even if
			 * the requested resource is already in the cache.
			 *
			 * @param	name	The resource name.
			 *
			 * @return	The refreshed resource, or a null-pointer if no reader could be found or
			 * 			the resource doesn't exist.
			 */
			template <typename ResourceType, typename ReaderType>
			OPENLIMA_DLL boost::shared_ptr<ResourceType>
					getRefreshedResource(const std::string& name) {

				if(!this->resourceExists(name))
					return boost::shared_ptr<ResourceType>();

				const std::vector<boost::shared_ptr<IAnonymousResourceReader> >& readerList =
					this->registeredReaders.find(&typeid(ResourceType))->second;

				BOOST_FOREACH(boost::shared_ptr<IAnonymousResourceReader> anonymousReader,
						readerList) {
					boost::shared_ptr<IResourceReader<ResourceType> > reader =
						boost::dynamic_pointer_cast<IResourceReader<ResourceType> >(anonymousReader);

					if(&typeid(*reader) == &typeid(ReaderType)) {
						boost::shared_ptr<std::istream> istream = this->openResourceStream(name);
						boost::shared_ptr<ResourceType> sPtr = reader->readResource(*istream);
						this->closeResourceStream(istream);
						this->cachedResources[name] = sPtr;
						return sPtr;
					}
				}

				return boost::shared_ptr<ResourceType>();

			}

		};

	}
}

#endif /* OPENLIMA_UTIL_RESOURCEMANAGER_HPP */
