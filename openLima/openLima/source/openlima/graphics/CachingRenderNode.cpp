// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/CachingRenderNode.hpp>


namespace openlima {
	namespace graphics {

		CachingRenderNode::CachingRenderNode() {
			this->validCache = false;
			this->glList = 0;
		}

		CachingRenderNode::~CachingRenderNode() {
			// Empty
		}


		void CachingRenderNode::invalidate() {
			this->validCache = false;
		}

		bool CachingRenderNode::isValid() const {
			return this->validCache;
		}

		void CachingRenderNode::render() {
			if(this->validCache) {
				glCallList(this->glList);
			} else {
				if(!glIsList(this->glList))
					this->glList = glGenLists(1);

				glNewList(this->glList, GL_COMPILE_AND_EXECUTE);
				RenderNode::render();
				glEndList();

				this->validCache = true;
			}
		}

	}
}
