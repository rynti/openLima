// Copyright (C) 2011 Robert Boehm
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

		/**
		 * A basic mesh. Doesn't have any functionality, use StaticMesh instead.
		 * Will provide much more functionality in the future.
		 *
		 * @sa	IRenderable
		 * @sa	StaticMesh
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class Mesh : public IRenderable {
		protected:

			/**
			 * Makes this class not instanceable, use specializations instead.
			 */
			OPENLIMA_DLL Mesh() {}

		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Mesh() {}

			/**
			 * Renders this mesh.
			 */
			OPENLIMA_DLL virtual void render() = 0;

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_MESH_HPP */
