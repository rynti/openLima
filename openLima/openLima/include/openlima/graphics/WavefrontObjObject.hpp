// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_WAVEFRONTOBJOBJECT_HPP
#define OPENLIMA_GRAPHICS_WAVEFRONTOBJOBJECT_HPP

#include <openlima/util/macros.hpp>
#include <boost/smart_ptr.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/graphics/StaticMesh.hpp>
#include <openlima/graphics/WavefrontObjMaterial.hpp>


namespace openlima {
	namespace graphics {

		class WavefrontObjObject : public IRenderable {
		public:
			boost::shared_ptr<WavefrontObjMaterial> material;
			boost::shared_ptr<StaticMesh> mesh;

			//OPENLIMA_DLL WavefrontObjObject();
			//OPENLIMA_DLL virtual ~WavefrontObjObject();

			OPENLIMA_DLL void render();
		};

	}
}

#endif /* OPENLIMA_GRAPHICS_WAVEFRONTOBJOBJECT_HPP */