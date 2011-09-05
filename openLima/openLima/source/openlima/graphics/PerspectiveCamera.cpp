// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/macros.hpp>
#include <openlima/graphics/PerspectiveCamera.hpp>
#include <openlima/sil/sigl.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		PerspectiveCamera::PerspectiveCamera(Real fov) {
			this->fov = fov;
		}

		PerspectiveCamera::~PerspectiveCamera() {
			// Empty
		}


		void PerspectiveCamera::modifyProjection(Vector2i dimensions) {
			gluPerspective(fov,
				(double)dimensions.x / (double)dimensions.y,
				0.01, 200.0);
		}

		void PerspectiveCamera::render() {
#ifdef OPENLIMA_PRECISE_REAL
			glRotated(rotation.x, 1.0, 0.0, 0.0);
			glRotated(rotation.z, 0.0, 0.0, 1.0);
			glRotated(rotation.y, 0.0, 1.0, 0.0);
			glTranslated(position.x, position.y, position.z);
#else
			glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
			glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
			glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
			glTranslatef(position.x, position.y, position.z);
#endif
		}

	}
}
