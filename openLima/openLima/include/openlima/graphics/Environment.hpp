// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_ENVIRONMENT_HPP
#define OPENLIMA_GRAPHICS_ENVIRONMENT_HPP

#include <boost/smart_ptr.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector2.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/ICamera.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/graphics/IProjectionModifier.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * An environment which manages the lightning, cameras and contains a render node that gets
		 * drawn.
		 */
		class Environment {
		private:

			/** The "root" render node. */
			RenderNode renderNode;

			/** A render initializer. Can do pre-render stuff like camera offset. */
			boost::shared_ptr<IRenderable> renderInitializer;

			/** A projection modifier, that sets up the projection matrix. */
			boost::shared_ptr<IProjectionModifier> projectionModifier;

		public:
			
			/**
			 * Creates a new environment.
			 */
			OPENLIMA_DLL Environment();
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~Environment();
			
			
			/**
			 * Sets the projection modifier for this environment.
			 *
			 * @param projectionModifier	The projection modifier.
			 */
			OPENLIMA_DLL void setProjectionModifier(
				boost::shared_ptr<IProjectionModifier> projectionModifier);
			
			/**
			 * Sets the render initializer for this environment.
			 *
			 * @param renderInitializer	The render initializer.
			 */
			OPENLIMA_DLL void setRenderInitializer(
				boost::shared_ptr<IRenderable> renderInitializer);

			/**
			 * Sets the camera for this environment.
			 *
			 * @param camera	The camera.
			 */
			OPENLIMA_DLL void setCamera(boost::shared_ptr<ICamera> camera);
			
			/**
			 * Returns the projection modifier of this environment.
			 *
			 * @return The projection modifier of this environment.
			 */
			OPENLIMA_DLL boost::shared_ptr<IProjectionModifier> getProjectionModifier();
			
			/**
			 * Returns the render initializer of this environment.
			 *
			 * @return The render initializer of this environment.
			 */
			OPENLIMA_DLL boost::shared_ptr<IRenderable> getRenderInitializer();
			
			/**
			 * Returns the root render node of this environment.
			 *
			 * @return The root render node of this environment.
			 */
			OPENLIMA_DLL RenderNode& getRenderNode();
			
			/**
			 * Renders this environment.
			 */
			OPENLIMA_DLL void render(openlima::util::Vector2i dimensions);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_ENVIRONMENT_HPP */