// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_ENVIRONMENT_HPP
#define OPENLIMA_GRAPHICS_ENVIRONMENT_HPP

#include <vector>

#include <boost/smart_ptr.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector2.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/ICamera.hpp>
#include <openlima/graphics/ILight.hpp>
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

			/** The lights in this environment. */
			std::vector<boost::shared_ptr<ILight> > lights;
			
			/** The color of the ambience in this environment. */
			openlima::util::Color ambientColor;

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
			 * Returns the color of the ambient light of this environment.
			 *
			 * @return	The color of the ambient light of this environment.
			 */
			OPENLIMA_DLL openlima::util::Color getAmbientColor() const;
			
			/**
			 * Sets the color of the ambient light for this environment.
			 *
			 * @param ambientColor	The color for the ambient light.
			 */
			OPENLIMA_DLL void setAmbientColor(const openlima::util::Color ambientColor);
			
			/**
			 * Adds the given light to this environment.
			 *
			 * @param light	The light.
			 */
			OPENLIMA_DLL void addLight(boost::shared_ptr<ILight> light);
			
			/**
			 * Removes the given light from this environment.
			 *
			 * @param light	The light.
			 */
			OPENLIMA_DLL void removeLight(boost::shared_ptr<ILight> light);
			
			/**
			 * Removes all lights from this environment.
			 */
			OPENLIMA_DLL void clearLights();
			
			/**
			 * Renders this environment.
			 */
			OPENLIMA_DLL void render(openlima::util::Vector2i dimensions);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_ENVIRONMENT_HPP */