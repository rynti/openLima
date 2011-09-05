// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_PERSPECTIVECAMERA_HPP
#define OPENLIMA_GRAPHICS_PERSPECTIVECAMERA_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Vector2.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/ICamera.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * A perspective camera that sets up a perspective projection.
		 *
		 * @see ICamera
		 */
		class PerspectiveCamera : public ICamera {
		private:

			/** The field of view for this camera. */
			openlima::util::Real fov;

		public:

			/** The position of this camera. */
			openlima::util::Vector3f position;

			/** The rotation of this camera. */
			openlima::util::Vector3f rotation;

			
			/**
			 * Creates a new perspective camera.
			 *
			 * @param fov	The field of view of this camera.
			 */
			OPENLIMA_DLL PerspectiveCamera(openlima::util::Real fov);
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~PerspectiveCamera();

			
			/**
			 * Sets up a perspective projection. The dimensions are needed to calculate the aspect
			 * ratio.
			 *
			 * @param dimensions	The screen dimensions
			 */
			OPENLIMA_DLL virtual void modifyProjection(openlima::util::Vector2i dimensions) const;
			
			/**
			 * Renders this camera. In this case, modifies the current matrix to be affected by the
			 * position and rotation of this camera.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_PERSPECTIVECAMERA_HPP */
