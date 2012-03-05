// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_WAVEFRONTOBJMATERIALLIBRARY_HPP
#define OPENLIMA_GRAPHICS_WAVEFRONTOBJMATERIALLIBRARY_HPP

#include <openlima/util/macros.hpp>
#include <map>
#include <string>
#include <boost/smart_ptr.hpp>


namespace openlima {
	namespace graphics {

		class WavefrontObjMaterialLibrary {
		private:
			std::map<string, boost::shared_ptr<WavefrontObjMaterial>> materials;

		public:
			OPENLIMA_DLL boost::shared_ptr<WavefrontObjMaterial> getMaterial(string name);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_WAVEFRONTOBJMATERIALLIBRARY_HPP */