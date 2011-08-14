#include "Path.hpp"


namespace openlima {
	namespace util {

		Path::Path(const char* unixPath) {
			size_t pathLength = strlen(unixPath);
			this->nativePath = new char[pathLength + 1];
			
			for(size_t i = 0; i < pathLength; i++) {
#ifdef L_WIN
				if(unixPath[i] == '/') {
					this->nativePath[i] = '\\';
				} else {
					this->nativePath[i] = unixPath[i];
				}
#else
				this->nativePath[i] = unixPath[i];
#endif
			}

			this->nativePath[pathLength] = 0;
		}

		Path::~Path() {
			delete this->nativePath;
		}

		const char* Path::getNative() {
			return this->nativePath;
		}

	}
}