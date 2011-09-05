// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_ICAMERA_HPP
#define OPENLIMA_GRAPHICS_ICAMERA_HPP

#include <openlima/util/macros.hpp>
#include <openlima/graphics/IProjectionModifier.hpp>
#include <openlima/graphics/IRenderable.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * An interface for cameras. Has a render()-method that should be called BEFORE rendering
		 * any other object of the scene, and a modifyProjectionMatrix(Vector2i)-method that
		 * modifies the projection matrix.
		 *
		 * @see IProjectionModifier
		 * @see IRenderable
		 */
		class ICamera : public IProjectionModifier, public IRenderable {
		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~ICamera() {}

		};
		
	}
}

#endif /* OPENLIMA_GRAPHICS_ICAMERA_HPP */