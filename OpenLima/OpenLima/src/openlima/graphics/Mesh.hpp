// Copyright (C) 2011 Robert Böhm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_MESH_HPP
#define OPENLIMA_GRAPHICS_MESH_HPP


#include "../util/macros.hpp"
#include "IRenderable.hpp"



namespace openlima {
	namespace graphics {

		class Mesh : public IRenderable {
		protected:
			OPENLIMA_DLL Mesh() {}

		public:
			OPENLIMA_DLL virtual ~Mesh() {}
			OPENLIMA_DLL virtual void render() = 0;
			//TODO: Modifier

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_MESH_HPP */