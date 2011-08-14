#ifndef OPENLIMA_UTIL_PATH_HPP
#define OPENLIMA_UTIL_PATH_HPP

#include "macros.hpp"


namespace openlima {
	namespace util {

		class Path {
		private:

			char* nativePath;

		public:
			
			L_DLL Path(const char* unixPath);

			L_DLL virtual ~Path();


			L_DLL const char* getNative();

		};

	}
}

#endif /* OPENLIMA_UTIL_PATH_HPP */