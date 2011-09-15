// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/PointLight.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		PointLight::PointLight(Vector3f position, Color ambient, Color diffuse, Color specular)
				: position(position), ambient(ambient), diffuse(diffuse), specular(specular) {
			// Empty
		}

		PointLight::~PointLight() {
			// Empty
		}


		void PointLight::setLight(u32 index) {
			GLenum lightIndex = GL_LIGHT0 + index;

			float positionFv[] = {
				(float)position.x, (float)position.y,
				(float)position.z, 0.0f
			};
			glLightfv(lightIndex, GL_POSITION, positionFv);

			float ambientFv[] = {
				(float)ambient.r, (float)ambient.g,
				(float)ambient.b, (float)ambient.a
			};
			glLightfv(lightIndex, GL_AMBIENT, ambientFv);

			float diffuseFv[] = {
				(float)diffuse.r, (float)diffuse.g,
				(float)diffuse.b, (float)diffuse.a
			};
			glLightfv(lightIndex, GL_DIFFUSE, diffuseFv);

			float specularFv[] = {
				(float)specular.r, (float)specular.g,
				(float)specular.b, (float)specular.a
			};
			glLightfv(lightIndex, GL_SPECULAR, specularFv);

		}

	}
}
