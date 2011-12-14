// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/ScalingRenderNode.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		ScalingRenderNode::ScalingRenderNode(Vector3f scale) : scale(scale) {
			// Empty
		}

		ScalingRenderNode::~ScalingRenderNode() {
			// Empty
		}


		void ScalingRenderNode::render() {
#ifdef OPENLIMA_PRECISE_REAL
			glPushMatrix();
			glScaled(scale.x, scale.y, scale.z);
			RenderNode::render();
			glPopMatrix();
#else
			glPushMatrix();
			glScalef(scale.x, scale.y, scale.z);
			RenderNode::render();
			glPopMatrix();
#endif
		}

	}
}
