// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/CachedRenderable.hpp>


namespace openlima {
	namespace graphics {

		CachedRenderable::CachedRenderable(boost::shared_ptr<IRenderable> renderable) {
			this->renderable = renderable;
			this->validCache = false;
			this->glList = 0;
		}

		CachedRenderable::~CachedRenderable() {
			// Empty
		}


		void CachedRenderable::render() {
			if(this->validCache) {
				glCallList(this->glList);
			} else {
				if(!glIsList(this->glList))
					this->glList = glGenLists(1);
				
				glNewList(this->glList, GL_COMPILE_AND_EXECUTE);
				this->renderable->render();
				glEndList();

				this->validCache = true;
			}
		}

		void CachedRenderable::invalidate() {
			this->validCache = false;
		}

		bool CachedRenderable::isValid() {
			return this->validCache;
		}

	}
}
