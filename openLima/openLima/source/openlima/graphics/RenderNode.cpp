// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/smart_ptr.hpp>

#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/RenderNode.hpp>

using namespace boost;


namespace openlima {
	namespace graphics {

		RenderNode::RenderNode() {
			// Empty
		}

		RenderNode::~RenderNode() {
			// Empty
		}


		void RenderNode::addChild(shared_ptr<IRenderable> child) {
			this->children.push_back(child);
		}

		void RenderNode::clearChildren() {
			this->children.clear();
		}

		void RenderNode::render() {
			for(size_t i = 0; i < this->children.size(); i++) {
				this->children.at(i)->render();
			}
		}

	}
}
