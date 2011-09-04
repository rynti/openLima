// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/TranslatingRenderNode.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		TranslatingRenderNode::TranslatingRenderNode(Vector3f translation) : translation(translation) {
			// Empty
		}

		TranslatingRenderNode::~TranslatingRenderNode() {
			// Empty
		}


		void TranslatingRenderNode::render() {
#ifdef OPENLIMA_PRECISE_REAL
			glPushMatrix();
			glTranslated(translation.x, translation.y, translation.z);
			RenderNode::render();
			glPopMatrix();
#else
			glPushMatrix();
			glTranslatef(translation.x, translation.y, translation.z);
			RenderNode::render();
			glPopMatrix();
#endif
		}

	}
}
