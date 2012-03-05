// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/graphics/SimplePass.hpp>
#include <openlima/sil/sigl.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		SimplePass::SimplePass(Color ambient, Color diffuse, Color specular, Color emission,
				float shininess) : shininess(shininess) {
			this->ambient = new float[4];
			this->diffuse = new float[4];
			this->specular = new float[4];
			this->emission = new float[4];
			ambient.fill(this->ambient);
			diffuse.fill(this->diffuse);
			specular.fill(this->specular);
			emission.fill(this->emission);
		}

		SimplePass::~SimplePass() {
			delete [] ambient;
			delete [] diffuse;
			delete [] specular;
			delete [] emission;
		}

		void SimplePass::setProperties() {
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, emission);
			glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		}

		void SimplePass::unsetProperties() {
		}

	}
}
