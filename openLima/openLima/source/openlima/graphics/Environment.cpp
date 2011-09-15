// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <iostream>

#include <openlima/util/Vector2.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/Environment.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		Environment::Environment() {
			// Empty
		}

		Environment::~Environment() {
			// Empty
		}


		void Environment::setProjectionModifier(
				boost::shared_ptr<IProjectionModifier> projectionModifier) {
			this->projectionModifier = projectionModifier;
		}

		void Environment::setRenderInitializer(boost::shared_ptr<IRenderable> renderInitializer) {
			this->renderInitializer = renderInitializer;
		}
		boost::shared_ptr<IProjectionModifier> Environment::getProjectionModifier() {
				return projectionModifier;
		}

		boost::shared_ptr<IRenderable> Environment::getRenderInitializer() {
			return renderInitializer;
		}

		void Environment::setCamera(boost::shared_ptr<ICamera> camera) {
			this->projectionModifier = camera;
			this->renderInitializer = camera;
		}

		RenderNode& Environment::getRenderNode() {
			return renderNode;
		}
			
		Color Environment::getAmbientColor() const {
			return this->ambientColor;
		}
			
		void Environment::setAmbientColor(const Color ambientColor) {
			this->ambientColor = ambientColor;
		}
		
		void Environment::addLight(boost::shared_ptr<ILight> light) {
			lights.push_back(light);
		}

		void Environment::removeLight(boost::shared_ptr<ILight> light) {
			// TODO
		}

		void Environment::clearLights() {
			lights.clear();
		}


		void Environment::render(Vector2i dimensions) {
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if(projectionModifier) projectionModifier->modifyProjection(dimensions);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			if(renderInitializer) renderInitializer->render();

			float ambientColorFv[] = {
				ambientColor.r,
				ambientColor.g,
				ambientColor.b,
				ambientColor.a,
			};
			glLightModelfv(GL_AMBIENT, ambientColorFv);

			for(size_t i = 0; i < 8; i++) {
				if(i < lights.size()) {
					glEnable(GL_LIGHT0 + i);
					lights.at(i)->setLight(i);
				} else {
					glDisable(GL_LIGHT0 + i);
				}
			}
			this->renderNode.render();

		}

	}
}