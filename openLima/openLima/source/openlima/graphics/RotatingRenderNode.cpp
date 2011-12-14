// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/RotatingRenderNode.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		RotatingRenderNode::RotatingRenderNode(Real angle, Vector3f axis) : angle(angle), axis(axis) {
			// Empty
		}

		RotatingRenderNode::~RotatingRenderNode() {
			// Empty
		}


		void RotatingRenderNode::render() {
#ifdef OPENLIMA_PRECISE_REAL
			glPushMatrix();
			glRotated(angle, axis.x, axis.y, axis.z);
			RenderNode::render();
			glPopMatrix();
#else
			glPushMatrix();
			glRotatef(angle, axis.x, axis.y, axis.z);
			RenderNode::render();
			glPopMatrix();
#endif
		}

	}
}
