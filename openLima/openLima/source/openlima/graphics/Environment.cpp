// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

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

		void Environment::render(Vector2i dimensions) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if(projectionModifier) projectionModifier->modifyProjection(dimensions);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			if(renderInitializer) renderInitializer->render();
			this->renderNode.render();
		}

	}
}