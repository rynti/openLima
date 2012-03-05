// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/graphics/WavefrontObjObject.hpp>


namespace openlima {
	namespace graphics {

		void WavefrontObjObject::render() {
			this->material->render(this->mesh);
		}

	}
}
