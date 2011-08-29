// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <openlima/util/FileResourceManager.hpp>

using namespace std;
using namespace boost::filesystem;


namespace openlima {
	namespace util {

		FileResourceManager::FileResourceManager()
			: parentDirectory("./") {

		}

		FileResourceManager::FileResourceManager(const std::string& parent)
			: parentDirectory(parent) {

		}

		FileResourceManager::~FileResourceManager() {
			// Empty
		}

		boost::shared_ptr<istream> FileResourceManager::openResourceStream(
				const string& name) const {
			path p(parentDirectory);
			p /= name;
			return boost::make_shared<boost::filesystem::ifstream>(p);
		}

		void FileResourceManager::closeResourceStream(boost::shared_ptr<istream> in) const {
			boost::shared_ptr<boost::filesystem::ifstream> stream =
				boost::dynamic_pointer_cast<boost::filesystem::ifstream>(in);

			stream->close();
		}

		bool FileResourceManager::resourceExists(const std::string& name) const {
			path p(parentDirectory);
			p /= name;
			return exists(p);
		}

	}
}
